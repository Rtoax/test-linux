// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_SK_SKB
 *
 * Socket SKB programs are called on L4 data streams to parse L7 messages
 * and/or to determine if the L4/L7 messages should be allowed, blocked or
 * redirected.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("sk_skb")
int prog_skb_drop(struct __sk_buff *skb)
{
	return SK_DROP;
}

char _license[] SEC("license") = "GPL";
