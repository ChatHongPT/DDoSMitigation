#include<arpa/inet.h>
#include<linux/bpf.h>
#include<linux/if_ether.h>
#include<linux/ip.h>
#include<linux/udp.h>
#include<bpf/bpf_helpers.h>

SEC("prog")
int block_udp(struct xdp_md *ctx){
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx -> data;
    
    struct ethhdr *eth = data;
    struct iphdr *ip;
    struct udphdr *udp;
    
    if((void*)(eth+1) > data_end)
        return XDP_PASS;
    if(eth->h_proto != htons(ETH_P_IP))    
        return XDP_PASS;
    ip = (struct iphdr *)(eth+1);
    if ((void*)(ip+1)>data_end)
        return XDP_PASS;
    if(ip->protocol != IPPROTO_UDP)
        return XDP_PASS;
    udp = (struct udphdr *)(ip+1);
    if((void*)(udp+1)>data_end)
        return XDP_PASS
    if(udp->dest != htons(80))
        return XDP_PASS;
    return XDP_DROP;        
        
}
char _license[] SEC("license") = "GPL";
