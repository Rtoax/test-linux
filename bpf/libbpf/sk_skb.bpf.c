// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_SK_SKB
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("sk_skb")
int prog_skb_drop(struct __sk_buff *skb)
{
	return SK_DROP;
}

char _license[] SEC("license") = "GPL";
