/**
 * BPF_PROG_TYPE_NETFILTER
 *
 * This program type is used to implement a netfilter (aka iptables / nftables)
 * hook in eBPF.
 *
 * The hook can make a decision to drop or accept the packet by returning
 * NF_DROP (0) or NF_ACCEPT (1) respectively.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

#define NF_DROP         0
#define NF_ACCEPT       1
#define ETH_P_IP        0x0800
#define ETH_P_IPV6      0x86DD

SEC("netfilter")
int netfilter1(struct bpf_nf_ctx *ctx)
{
	struct __sk_buff *skb = (struct __sk_buff *)ctx->skb;

	switch (bpf_ntohs(skb->protocol)) {
	case ETH_P_IP:
		return NF_ACCEPT;
	case ETH_P_IPV6:
	default:
		return NF_DROP;
	}
}

char _license[] SEC("license") = "GPL";
