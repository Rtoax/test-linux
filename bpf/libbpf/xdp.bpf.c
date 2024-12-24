/**
 * BPF_PROG_TYPE_XDP
 *
 * XDP (Express Data Path) programs can attach to network devices and are
 * called for every incoming (ingress) packet received by that network device.
 * XDP programs can take quite a large number of actions, most prominent of
 * which are manipulation of the packet, dropping the packet, redirecting it
 * and letting it pass to the network stack.
 *
 * Notable use cases for XDP programs are for DDoS protection, Load Balancing,
 * and high-throughput packet filtering. If loaded with native driver support,
 * XDP programs will be called just after receiving the packet but before
 * allocating memory for a socket buffer. This call site makes XDP programs
 * extremely performant, especially in use cases where traffic is forwarded or
 * dropped a lot in comparison to other eBPF program types or techniques which
 * run after the relatively expensive socket buffer allocation process has
 * taken place, only to discard it.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>

#define ETH_P_IP	0x0800

#if defined(STRICT_SEC_NAME)
SEC("xdp")
#endif
int xdp_dummy_prog(struct xdp_md *ctx)
{
	return XDP_PASS;
}

#if defined(STRICT_SEC_NAME)
SEC("xdp")
#endif
int xdp_pass(struct xdp_md *ctx)
{
	int proto = 0;
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct ethhdr *ethhdr = data;
	static unsigned long icmp_count = 0;

	if (data + sizeof(struct ethhdr) > data_end) {
		bpf_printk("Not ether header");
		return XDP_PASS;
	}

	if (bpf_ntohs(ethhdr->h_proto) == ETH_P_IP) {
		struct iphdr *iphdr = data + sizeof(struct ethhdr);
		if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) <= data_end)
			proto = iphdr->protocol;
	}

	/**
	 * Only access to ingress_ifindex, egress_ifindex access deny, see
	 * 'xdp/devmap'.
	 */
	bpf_printk("xdp ingress %d", ctx->ingress_ifindex);

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

char __license[] SEC("license") = "GPL";
