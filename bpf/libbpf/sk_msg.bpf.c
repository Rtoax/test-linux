// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_SK_MSG
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

/**
 * return - SK_DROP or SK_PASS
 */
SEC("sk_msg")
int prog_skmsg_drop(struct __sk_buff *skb)
{
	return SK_DROP;
}

char _license[] SEC("license") = "GPL";
