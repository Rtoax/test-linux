#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("mysection")
int myprogram(struct xdp_md *ctx)
{
	int ipsize = 0;
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct ethhdr *eth = data;
	struct iphdr *ip;

	ipsize = sizeof(*eth);
	ip = data + ipsize;
	ipsize += sizeof(struct iphdr);
	if (data + ipsize > data_end) {
		return XDP_DROP;
	}

	if (ip->protocol == IPPROTO_TCP) {
		return XDP_DROP;
	}

	return XDP_PASS;
}
