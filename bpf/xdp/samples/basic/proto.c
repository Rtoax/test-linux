#include "vmlinux.h"
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>

#define SEC(NAME) __attribute__((section(NAME), used))

#define ETH_P_IP	0x0800		/* Internet Protocol packet	*/
#define ETH_P_IPV6	0x86DD		/* IPv6 over bluebook		*/


static __always_inline int handle_ipv4(struct xdp_md *xdp)
{
	return XDP_DROP;
}

static __always_inline int handle_ipv6(struct xdp_md *xdp)
{
	return XDP_DROP;
}

SEC("xdp")
int _xdp(struct xdp_md *xdp)
{
	void *data_end = (void *)(long)xdp->data_end;
	void *data = (void *)(long)xdp->data;
	struct ethhdr *eth = data;
	__u16 h_proto;

	if (eth + 1 > data_end)
		return XDP_DROP;

	h_proto = eth->h_proto;

	if (h_proto == bpf_htons(ETH_P_IP))
		return handle_ipv4(xdp);
	else if (h_proto == bpf_htons(ETH_P_IPV6))
		return handle_ipv6(xdp);
	else
		return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
