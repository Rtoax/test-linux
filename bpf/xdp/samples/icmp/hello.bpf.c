#include "vmlinux.h"
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>


#define ETH_P_IP	0x0800

SEC("xdp")
int ping(struct xdp_md *ctx)
{
	int protocol;
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct ethhdr *ethhdr = data;

	if (data + sizeof(struct ethhdr) > data_end) {
		bpf_printk("Not ether header");
		return XDP_PASS;
	}

	if (bpf_ntohs(ethhdr->h_proto) == ETH_P_IP) {
		struct iphdr *iphdr = data + sizeof(struct ethhdr);
		if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) <= data_end)
			protocol = iphdr->protocol;
	}

	switch (protocol) {
	case 1: /* icmp */
		bpf_printk("Hello ping");
		// return XDP_DROP;
		break;
	case 6: /* tcp */
		bpf_printk("Hello tcp");
		break;
	case 17: /* udp */
		bpf_printk("Hello udp");
		break;
	}
	return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
