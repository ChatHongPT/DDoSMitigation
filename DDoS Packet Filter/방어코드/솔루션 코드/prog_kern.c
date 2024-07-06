#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <arpa/inet.h>

struct record_rec {
	__u64 total;
    __u64 drop;
	__u64 pass;
};

struct{
        __uint(type, BPF_MAP_TYPE_LRU_HASH);
        __type(key, __u32);
        __type(value, struct record_rec);
        __uint(max_entries, 1);
} stats_show SEC(".maps");

struct record {
	__u64 rx_tcp_packets;
        __u64 tcp_data;
	__u64 time;
};

struct{
        __uint(type, BPF_MAP_TYPE_LRU_HASH);
        __type(key, __u32);
        __type(value, struct record);
        __uint(max_entries, 512);
} ip_stats SEC(".maps");

struct{
        __uint(type, BPF_MAP_TYPE_LRU_HASH);
        __type(key, __u32);
        __type(value, __u32);
        __uint(max_entries, 1);
} arp_table SEC(".maps");

struct{
        __uint(type, BPF_MAP_TYPE_LRU_HASH);
        __type(key, __u32);
        __type(value, __u32);
        __uint(max_entries, 512);
} ban_ip SEC(".maps");

struct{ //0=pps 1=bps
        __uint(type, BPF_MAP_TYPE_ARRAY);
        __type(key, __u32);
        __type(value, __u64);
        __uint(max_entries, 2);
} inform SEC(".maps");

struct {
        __uint(type, BPF_MAP_TYPE_XSKMAP);
        __type(key, int);
        __type(value, int);
        __uint(max_entries, 2);
} xsk_map SEC(".maps");

static int int_index = 0;
static __u32 con = 1;
static __u32 con_v = 2;
SEC("xdp")
int process(struct xdp_md *ctx) {

	void *data_end = (void *)(long)ctx->data_end;
	void *data     = (void *)(long)ctx->data;
	
	struct ethhdr *eth = data;
	if(eth+1>(struct ethhdr*)data_end)
		return XDP_DROP;
	struct record_rec stat_alloc;
	stat_alloc.total = 0;
	stat_alloc.drop = 0;
	stat_alloc.pass = 0;
	struct record_rec *stat = bpf_map_lookup_elem(&stats_show,&int_index);
	if(!stat){
		bpf_map_update_elem(&stats_show, &int_index, &stat_alloc, BPF_NOEXIST);
	}
	if(eth->h_proto != htons(ETH_P_IP)){
		if(eth->h_proto == htons(ETH_P_ARP)){
			__u32 *arp = bpf_map_lookup_elem(&arp_table, &con);
			if(!arp){
				if(!stat){stat = &stat_alloc;}
				stat->total++;
				stat->pass++;
				bpf_map_update_elem(&arp_table, &con, &con,BPF_NOEXIST);
				return XDP_PASS;
			} else {
				__sync_fetch_and_add(arp, 1);
				if(*arp >=10){
					if(!stat){stat = &stat_alloc;}

					stat->total++;
					stat->drop++;
					return XDP_DROP;
				}
				if(!stat){stat = &stat_alloc;}
				stat->total++;
				stat->pass++;
				return XDP_PASS;
			}
		}
		if(!stat){stat = &stat_alloc;}
		stat->total++;
		stat->drop++;
		return XDP_DROP;
	}
		
	struct iphdr *iph = (data + sizeof(struct ethhdr));
	if(iph+1>(struct iphdr*)data_end)
		return XDP_DROP;
	__u64 now = (__u64)bpf_ktime_get_ns();
       	__u32 ip = iph->saddr;
	struct record *value = bpf_map_lookup_elem(&ip_stats, &ip);
	struct record recd;
	int *detect_v = bpf_map_lookup_elem(&ban_ip,&ip);
	if(detect_v){
		if(!stat){stat = &stat_alloc;}
		stat->total++;
		stat->drop++;
		return XDP_DROP;
	}
	if(iph->saddr == iph->daddr){
		if(!stat){stat = &stat_alloc;}
		stat->total++;
		stat->drop++;
		return XDP_DROP;
	}
	if(iph->protocol == IPPROTO_ICMP || iph->protocol == IPPROTO_UDP){
		if(!stat){stat = &stat_alloc;}
		stat->total++;
		stat->drop++;
		return XDP_DROP;
	}
	if(iph->protocol == IPPROTO_TCP){
		struct tcphdr *tcph = (data+sizeof(struct ethhdr) + (iph->ihl*4));
            	if(tcph+1>(struct tcphdr*)data_end)
               		return XDP_DROP;
		if(tcph->rst){
			if(!stat){stat = &stat_alloc;}
			stat->total++;
			stat->drop++;
			return XDP_DROP;
		}
		else
		{
          		__u64 len_frame = (__u64)(ctx->data_end - ctx->data);
           		__u64 len_hdr = (__u64)(sizeof(struct ethhdr)+iph->ihl*4+ tcph->doff*4);
         		__u64 payload = (len_frame-len_hdr);
			
			if(payload > 1400){
				if(!stat){stat = &stat_alloc;}
				stat->total++;
				stat->drop++;
				return XDP_DROP;
			}
			if(!value){
                	        recd.rx_tcp_packets = 1;
                	        recd.tcp_data = payload;
				recd.time = now;
				bpf_map_update_elem(&ip_stats, &ip, &recd, BPF_NOEXIST);
				if(tcph->syn){ // First SYN Drop
					if(!stat){stat = &stat_alloc;}
					stat->total++;
					stat->drop++;
					return XDP_DROP;
				}
				if(!stat){stat = &stat_alloc;}
				stat->total++;
				stat->pass++;
				return bpf_redirect_map(&xsk_map, int_index, 0);

			}
			value->rx_tcp_packets++;
        	        value->tcp_data += payload;
			__u64 off = now - value->time;
			if(off>=1000000000){
				value->time = now;
				__u64 pps = (value->rx_tcp_packets*1000000000)/off;
				value->rx_tcp_packets = 0;
				__u32 i_pps = 0;
				__u32 i_bps = 1;
				__u64 *info = bpf_map_lookup_elem(&inform,&i_pps);
			       	if(!info){
					bpf_map_update_elem(&inform,&i_pps,&pps,BPF_NOEXIST);
				} else {	
					bpf_map_update_elem(&inform,&i_pps,&pps,BPF_EXIST);
				}
                		if(pps >= 6){
                        		bpf_map_update_elem(&ban_ip,&ip,&pps,BPF_NOEXIST);
                        		bpf_map_delete_elem(&ip_stats,&ip);
					if(!stat){stat = &stat_alloc;}

					stat->total++;
					stat->drop++;
					return XDP_DROP;
				}
				__u64 bps = (value->tcp_data/(off/1000000000));
				value->tcp_data = 0;
                                __u64 *info_b = bpf_map_lookup_elem(&inform,&i_bps);
                                if(!info_b){
                                        bpf_map_update_elem(&inform,&i_bps,&bps,BPF_NOEXIST);
                                }else{
                                	bpf_map_update_elem(&inform,&i_pps,&bps,BPF_EXIST);
				}
				if(bps >= 2000){
					bpf_map_update_elem(&ban_ip,&ip,&con,BPF_NOEXIST);
					bpf_map_delete_elem(&ip_stats,&ip);
					if(!stat){stat = &stat_alloc;}
					stat->total++;
					stat->drop++;
					return XDP_DROP;
				}
				if(!stat){stat = &stat_alloc;}
				stat->total++;
				stat->pass++;
                		return bpf_redirect_map(&xsk_map, int_index, 0);

			}
			if(!stat){stat = &stat_alloc;}

			stat->total++;
			stat->pass++;
			return bpf_redirect_map(&xsk_map, int_index, 0);
		}
	}
	if(!stat){stat = &stat_alloc;}

	stat->total++;
	stat->drop++;
	return XDP_DROP;
}

char _license[] SEC("license") = "GPL";
