#include "vmlinux.h"
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>


#define ETH_P_IP	0x0800

SEC("xdp")
int ping(struct xdp_md *ctx)
{
	int proto = 0;
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct ethhdr *ethhdr = data;
	static unsigned long icmp_count = 0;

	if ((void *)(ethhdr + 1) > data_end) {
		bpf_printk("Not ether header");
		return XDP_PASS;
	}

	if (bpf_ntohs(ethhdr->h_proto) == ETH_P_IP) {
		struct iphdr *iphdr = data + sizeof(struct ethhdr);
		if ((void *)(iphdr + 1) <= data_end)
			proto = iphdr->protocol;
	}

	switch (proto) {
	case IPPROTO_ICMP: /* 1 */
		bpf_printk("Hello icmp %ld", icmp_count++);
		if (icmp_count % 2)
			return XDP_DROP;
		break;
	case IPPROTO_TCP: /* 6 */
		bpf_printk("Hello tcp");
		break;
	case IPPROTO_UDP: /* 17 */
		bpf_printk("Hello udp");
		break;
	}
	return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
