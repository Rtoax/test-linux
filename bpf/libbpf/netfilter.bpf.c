/**
 * BPF_PROG_TYPE_NETFILTER
 *
 * This program type is used to implement a netfilter (aka iptables / nftables)
 * hook in eBPF.
 *
 * The hook can make a decision to drop or accept the packet by returning
 * NF_DROP (0) or NF_ACCEPT (1) respectively.
 *
 * linux commit fd9c663b9ad6 ("bpf: minimal support for programs hooked into
 * netfilter framework") v6.3-rc6-1646-gfd9c663b9ad6 support.
 */
#include "vmlinux.h"
#include <linux/version.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

#define NF_DROP         0
#define NF_ACCEPT       1
#define ETH_P_IP        0x0800
#define ETH_P_IPV6      0x86DD

#ifndef LINUX_VERSION_CODE
#error "Not found LINUX_VERSION_CODE in linux/version.h"
#endif

#if LINUX_VERSION_CODE > KERNEL_VERSION(6, 3, 0)
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
#else
#warning "only kernel >= v6.3-rc6 support BPF_PROG_TYPE_NETFILTER"
#endif

char _license[] SEC("license") = "GPL";
