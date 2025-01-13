#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>
#include "xdp_simple.h"


#define ETH_P_IP	0x0800

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 128);
	__type(key, u32);
	__type(value, struct ipv4_addr_t);
} map_blacklist SEC(".maps");


SEC("xdp")
int xdp_dummy_prog(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct ethhdr *ethhdr = data;
	struct iphdr *iphdr;
	struct ipv4_addr_t *black;

	if ((void *)(ethhdr + 1) > data_end)
		return XDP_PASS;

	if (bpf_ntohs(ethhdr->h_proto) != ETH_P_IP)
		return XDP_PASS;

	iphdr = data + sizeof(struct ethhdr);
	if ((void *)(iphdr + 1) > data_end)
		return XDP_PASS;

	black = bpf_map_lookup_elem(&map_blacklist, &iphdr->saddr);
	if (black) {
		bpf_printk("xdp drop address 0x%lx packet in blacklist.",
			   iphdr->saddr);
		return XDP_DROP;
	}

	bpf_printk("xdp rx pkt from ifindex %d, saddr 0x%x, len %ld",
		   ctx->ingress_ifindex, iphdr->saddr,
		   (u64)(ctx->data_end - ctx->data));

	return XDP_PASS;
}

char __license[] SEC("license") = "GPL";
