//
// AF_XDP Socket 코드 사용 출처 : xdp-tutorial, Advanced03-AF_XDP(2024.05월) 
// https://github.com/xdp-project/xdp-tutorial/blob/master/advanced03-AF_XDP/af_xdp_user.c
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <assert.h>

#include <linux/bpf.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <xdp/libxdp.h>
#include <xdp/xsk.h>

#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <linux/if_link.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>


#define NUM_FRAMES 4096
#define FRAME_SIZE XSK_UMEM__DEFAULT_FRAME_SIZE
#define RX_BATCH_SIZE      64
#define INVALID_UMEM_FRAME UINT64_MAX

//Packet Beat로의 데이터 전송 목적. 그러나 삭제할 수도 있음
#define TARGET_PORT 80
#define TARGET_IP "172.17.0.4" //packet beat 컨테이너 주소
#define BUFFER_SIZE 1400 

//쓰레드 선언 & 프로세스 종료 알림 -> 쓰레드 종료 유도
pthread_t tid1, tid2;
bool thread =true;

//umem 선언
struct xsk_umem_info {
        struct xsk_ring_prod fq;
        struct xsk_ring_cons cq;
        struct xsk_umem *umem;
        void *buffer;
};

//xsk 선언
struct xsk_socket_info {
        struct xsk_ring_cons rx;
        struct xsk_ring_prod tx;
        struct xsk_umem_info *umem;
        struct xsk_socket *xsk; 

        uint64_t umem_frame_addr[NUM_FRAMES];
        uint32_t umem_frame_free;

        uint32_t outstanding_tx;
};

static void xsk_free_umem_frame(struct xsk_socket_info *xsk, uint64_t frame){
        assert(xsk->umem_frame_free < NUM_FRAMES);

        xsk->umem_frame_addr[xsk->umem_frame_free++] = frame;
}
static uint64_t xsk_umem_free_frames(struct xsk_socket_info *xsk){
        return xsk->umem_frame_free;
}
static struct xsk_umem_info *configure_xsk_umem(void *buffer, uint64_t size){
        struct xsk_umem_info *umem;

        umem = calloc(1, sizeof(*umem));
        if (!umem)
                return NULL;

        int ret = xsk_umem__create(&umem->umem, buffer, size, &umem->fq, &umem->cq, NULL);
        if (ret) {
                return NULL;
        }
        umem->buffer = buffer;
        return umem;
}
static uint64_t xsk_alloc_umem_frame(struct xsk_socket_info *xsk){
        uint64_t frame;
        if (xsk->umem_frame_free == 0)
                return INVALID_UMEM_FRAME;

        frame = xsk->umem_frame_addr[--xsk->umem_frame_free];
        xsk->umem_frame_addr[xsk->umem_frame_free] = INVALID_UMEM_FRAME;
        return frame;
}

// 소켓 생성
static struct xsk_socket_info *xsk_configure_socket(struct xsk_umem_info *umem, int xsk_map_fd, int ifindex) {

        struct xsk_socket_config xsk_cfg; //XSK 등록시 사용하는 CONFIG 구조체
        struct xsk_socket_info *xsk_info; 

        uint32_t idx;
        int i;
        uint32_t prog_id;

        xsk_info = calloc(1, sizeof(*xsk_info));
        if (!xsk_info){
                return NULL;
        }
        
        const char *ifname = "eth0";
        __u32 if_queue = 0; 

        xsk_info->umem = umem;
        xsk_cfg.rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS;
        xsk_cfg.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
        xsk_cfg.xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST| XDP_FLAGS_DRV_MODE; // NIC 지원시 prog_kern.o 와 함께 offload 모드로 전환해야함
        xsk_cfg.bind_flags = XDP_USE_NEED_WAKEUP | XDP_COPY; // ZERO_COPY로 바꿔야함(지원하는 nic만 가능, 성능 향상의 핵심 기능)
        xsk_cfg.libbpf_flags = XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD; // 써야 prog_kern.o 프로그램 작동
        
        //소켓 생성
        int ret = xsk_socket__create(&xsk_info->xsk, ifname,if_queue, umem->umem, &xsk_info->rx, &xsk_info->tx, &xsk_cfg);
        if (ret<0){
                goto error_exit;
        }

        //소켓 등록
        ret = xsk_socket__update_xskmap(xsk_info->xsk, xsk_map_fd);
        if (ret){
                goto error_exit;
        }
        
        if (bpf_xdp_query_id(ifindex, XDP_FLAGS_UPDATE_IF_NOEXIST|XDP_FLAGS_DRV_MODE, &prog_id)){
                goto error_exit;
        }

        fprintf(stdout, "\n\t\t\t XDP - PID : %d\n",prog_id);
        
        for (i = 0; i < NUM_FRAMES; i++)
                xsk_info->umem_frame_addr[i] = i * FRAME_SIZE;
        xsk_info->umem_frame_free = NUM_FRAMES;
        
        //QUEUE 세팅 흐름 : reserve -> fill -> submit
        ret = xsk_ring_prod__reserve(&xsk_info->umem->fq,XSK_RING_PROD__DEFAULT_NUM_DESCS,&idx);
        if (ret != XSK_RING_PROD__DEFAULT_NUM_DESCS){ // 예외처리, 실제 일어나진 X
                goto error_exit;
        }
        fprintf(stdout, "\t\t\t Reserved ring field : %d\n",ret);
        //FillQ 에 OFFSET 전달, 저장 
        for (i = 0; i < XSK_RING_PROD__DEFAULT_NUM_DESCS; i ++)
                *xsk_ring_prod__fill_addr(&xsk_info->umem->fq, idx++) = xsk_alloc_umem_frame(xsk_info);
        //최종 Queue Submit
        xsk_ring_prod__submit(&xsk_info->umem->fq,XSK_RING_PROD__DEFAULT_NUM_DESCS);
        fprintf(stdout, "\t\t\t fill Q submit COMPLETE\n");
        return xsk_info;

error_exit:
        return NULL;
}

static void complete_tx(struct xsk_socket_info *xsk){
        unsigned int completed;
        uint32_t idx_cq;

        if (!xsk->outstanding_tx)
                return;

        sendto(xsk_socket__fd(xsk->xsk), NULL, 0, MSG_DONTWAIT, NULL, 0);

        completed = xsk_ring_cons__peek(&xsk->umem->cq,XSK_RING_CONS__DEFAULT_NUM_DESCS,&idx_cq);

        if (completed > 0) {
                for (int i = 0; i < completed; i++)
                        xsk_free_umem_frame(xsk,*xsk_ring_cons__comp_addr(&xsk->umem->cq,idx_cq++));

                xsk_ring_cons__release(&xsk->umem->cq, completed);
                xsk->outstanding_tx -= completed < xsk->outstanding_tx ? completed : xsk->outstanding_tx;
        }
}

// 삭제할 수 있는 부분
uint16_t ip_checksum(const struct iphdr *ip_header) {
   	uint32_t sum = 0;
   	const uint16_t *ptr = (const uint16_t *)ip_header;

   	for (size_t i = 0; i < sizeof(struct iphdr) / 2; ++i)
        	sum += *ptr++;
   	

   	while (sum >> 16) 
        	sum = (sum & 0xFFFF) + (sum >> 16);
    	return ~sum;
}

//패킷 실질적인 처리 부분 , USER-SPACE 에서 패킷 데이터를 다룰 수 있는 부분
static bool process_packet(struct xsk_socket_info *xsk, uint64_t addr, uint32_t len){
        uint8_t *pkt = xsk_umem__get_data(xsk->umem->buffer, addr); //UMEM에 저장된 프레임 데이터 접근

        int ret;
        uint32_t tx_idx = 0;
        uint8_t tmp_mac[ETH_ALEN];
       	struct ethhdr *eth = (struct ethhdr *) pkt; //Kernel 프로그램이 아니므로 경계검사 필요X
        struct iphdr *iph = (struct iphdr *) (eth + 1);
        struct tcphdr *tcph = (struct tcphdr *)(iph + 1);
        unsigned char dest_mac[ETH_ALEN] = {0x02, 0x42, 0xac, 0x11, 0x00, 0x03};
        memcpy(eth->h_source, eth->h_dest, ETH_ALEN);
        memcpy(eth->h_dest, dest_mac, ETH_ALEN);
	
	
        //Backend ip 세팅
        uint32_t dest_ip = inet_addr("172.17.0.3");
		
	iph->saddr = iph->daddr;
        iph->daddr = dest_ip;

        iph->check = 0;
        iph->check = ip_checksum(iph);
		
		
        ret = xsk_ring_prod__reserve(&xsk->tx, 1, &tx_idx);
        if (ret != 1) {
                return false;
        }

        xsk_ring_prod__tx_desc(&xsk->tx, tx_idx)->addr = addr;
        xsk_ring_prod__tx_desc(&xsk->tx, tx_idx)->len = len;
        xsk_ring_prod__submit(&xsk->tx, 1);
        xsk->outstanding_tx++;
        return true;
}

static void handle_receive_packets(struct xsk_socket_info *xsk){
        unsigned int rcvd, stock_frames, i;
        uint32_t idx_rx = 0, idx_fq = 0;
        int ret;

        rcvd = xsk_ring_cons__peek(&xsk->rx, RX_BATCH_SIZE, &idx_rx);
        if (!rcvd)
                return;
        //사용할 수 있는 공간 조사
        stock_frames = xsk_prod_nb_free(&xsk->umem->fq,xsk_umem_free_frames(xsk));

        if (stock_frames > 0) {
                ret = xsk_ring_prod__reserve(&xsk->umem->fq, stock_frames,&idx_fq);
                while (ret != stock_frames)
                        ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd,&idx_fq);
                for (i = 0; i < stock_frames; i++)
                        *xsk_ring_prod__fill_addr(&xsk->umem->fq, idx_fq++) =xsk_alloc_umem_frame(xsk);
                xsk_ring_prod__submit(&xsk->umem->fq, stock_frames);
        }
        for (i = 0; i < rcvd; i++) {
                uint64_t addr = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx)->addr;
                uint32_t len = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++)->len;
                if (!process_packet(xsk, addr, len))
                        xsk_free_umem_frame(xsk, addr);

        }
        xsk_ring_cons__release(&xsk->rx, rcvd);
        complete_tx(xsk);
}

static void rx_and_process(struct xsk_socket_info *xsk_socket) {
        struct pollfd fds[1];
        int ret, nfds = 1;

        memset(fds, 0, sizeof(fds));
        fds[0].fd = xsk_socket__fd(xsk_socket->xsk); 
        fds[0].events = POLLIN;

        while(thread) {
                ret = poll(fds, nfds, -1);  //thread = 프로그램의 유효성을 계속 검사 ,polling mode
                if (ret <= 0 || ret > 1)
                        continue;
                handle_receive_packets(xsk_socket); 
        }
}


int unload(int index){
        struct xdp_multiprog *prog = xdp_multiprog__get_from_ifindex(index);
        int err;
        if(!prog){
                fprintf(stderr,"[!] There is no XDP program on interface\n");
                return EXIT_FAILURE;
        }

        err = xdp_multiprog__detach(prog);
        if(err)
                fprintf(stderr,"[!] Can't detach XDP program!\n");
        fprintf(stdout,"\t\t\t[O] Detach all programs on interface\n");
        xdp_multiprog__close(prog);
        return EXIT_SUCCESS;
}
// 패킷 BEATS 로 데이터를 보내기 위한 부분 -> 아마 수정할 부분. //
void read_map_data(char *buffer, size_t buffer_size) {
        FILE *fp;
        char command[256];
        snprintf(command, sizeof(command), "bpftool map dump name inform");
        fp = popen(command, "r");
        if (fp == NULL) {
                printf("[!] Error!\n");
                return;
        }
        size_t file_read = fread(buffer, 1, buffer_size - 1, fp);
        if (file_read > 0) {
                buffer[file_read] = '\0';
        }
        pclose(fp);
}
// 파일 BEATS 로 데이터를 보내기 위한 부분 -> 아마 수정될 것 같습니다... //
void *send2packetbeat(void *arg) {

        char buffer[BUFFER_SIZE];
        struct sockaddr_in service;

        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd == -1) {
                fprintf(stderr,"[!] Socket creation failed..\n");
                pthread_exit(NULL);
        }

        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_port = htons(TARGET_PORT);
        service.sin_addr.s_addr = inet_addr(TARGET_IP);

        while (thread) {
                /*read_map_data(buffer, BUFFER_SIZE);
                if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&service, sizeof(service)) < 0) {
                        fprintf(stderr,"[!] Socket 'sendto' failed.. \n");
                        break;
                }
                printf("\n\t\t\t[O] Send data to Packet beat...\n");
		*/
                sleep(2);
        }

        close(sockfd);
        pthread_exit(NULL);
}
// ARP table reset 용도
void *init_map(void *arg){
        int *map_fd = (int*)arg;
        while(thread){
                sleep(10);
                int key = 0;
                int value = 0;
                bpf_map_update_elem(*map_fd,&key,&value,BPF_EXIST);
        }
        pthread_exit(NULL);
}

static void signal_int(int sig){
 
 	const char dev[] = "eth0";
        int ifidx = if_nametoindex(dev);
       	int err = unload(ifidx);
        if (err) {
                fprintf(stdout, "[O] interrupt success\n");
        }
	thread = false;
	pthread_cancel(tid1);
	pthread_cancel(tid2);
}


int main(void){
	char filename[] = "prog_kern.o";
	char progname[] = "process";
	char errmsg[1024];
	const char dev[] = "eth0";
	
	int err = 1,ret;
	int ifidx = if_nametoindex(dev);
	void *packet_buffer;

	signal(SIGINT,signal_int);

	if(!ifidx){
                fprintf(stderr,"[!] Couldn't find interface ID..\n");
                return err;	
	}
	
	DECLARE_LIBBPF_OPTS(bpf_object_open_opts, bpf_opts);
	DECLARE_LIBXDP_OPTS(xdp_program_opts, xdp_opts,
                            .open_filename = filename,
                            .prog_name = progname,
                            .opts = &bpf_opts);

	if (err = unload(ifidx)){
		fprintf(stderr,"[!] Couldn't unload All XDP Program...\n");
		return err;
	}
	fprintf(stderr,"\t\t\t[O] Unloaded all xdp program \n");

	struct xdp_program *prog = xdp_program__create(&xdp_opts);
	err = libxdp_get_error(prog);
	if (err) {
		libxdp_strerror(err, errmsg, sizeof(errmsg));
		fprintf(stderr, "[!] Couldn't create xdp program.. \n >> %s \n",errmsg);
		goto error;
	}

	err = xdp_program__attach(prog, ifidx, XDP_MODE_NATIVE, 0);
	if (err) {
		fprintf(stderr, "[!] Couldn't attach xdp program..\n");
		goto error;
	}

	fprintf(stdout, "\t\t\t[O] XDP Program Load Success !!\n");

        struct bpf_map *map = bpf_object__find_map_by_name(xdp_program__bpf_obj(prog), "xsk_map");
        int xsk_map_fd = bpf_map__fd(map);
        if (xsk_map_fd < 0) {
                fprintf(stderr, "> There is no xmap on program.. \n");
                goto error;

        }
	

        struct bpf_map *arp_map = bpf_object__find_map_by_name(xdp_program__bpf_obj(prog), "arp_table");
        int arp_map_fd = bpf_map__fd(arp_map);
        if (arp_map_fd < 0) {
                fprintf(stderr, "[!] There is no arp map on program.. \n");
                goto error;
	}
	if(pthread_create(&tid1,NULL,init_map,&arp_map_fd) != 0)
		goto error;
	if(pthread_create(&tid2,NULL,send2packetbeat,NULL) != 0)
		goto error;
	
	fprintf(stdout, "\n\t\t\t>> Thread started <<\n"); //쓰레드 생성 2가지 1. ARP_TABLE reset 2. File beat에 정보 전송(이 부분은 여유가 있을 때만 채택, 아마 삭제할 예정)
                                                
        struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};
        if (setrlimit(RLIMIT_MEMLOCK, &rlim)) {
                fprintf(stderr, "[!] Failed to rlimit set.... \n");
                goto error;
        }

        uint64_t packet_buffer_size = NUM_FRAMES * FRAME_SIZE;
        if (posix_memalign(&packet_buffer,getpagesize(),packet_buffer_size)) {
                fprintf(stderr, "[!] Failed to memalign... \n");
                goto error;
        }

        struct xsk_umem_info *umem = configure_xsk_umem(packet_buffer, packet_buffer_size);
        if (umem == NULL) {
                fprintf(stderr, "[!] Failed to UMEM set.... \n");
                goto error;
        }

        struct xsk_socket_info *xsk_socket = xsk_configure_socket(umem, xsk_map_fd,ifidx);
        if (xsk_socket == NULL) {
                fprintf(stderr, "[!] Failed to Socket set.... \n");
                xsk_umem__delete(umem->umem);
                goto error;
        }
        fprintf(stdout, "\n\t\t\t>> Program started <<\n");

        rx_and_process(xsk_socket);

        xsk_socket__delete(xsk_socket->xsk);
        xsk_umem__delete(umem->umem);
        free(xsk_socket);
        free(umem);
	xdp_program__close(prog);
	return 0;

error:
	xdp_program__close(prog);
	return err;
}
