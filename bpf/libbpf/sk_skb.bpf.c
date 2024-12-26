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

/**
 * BPF_MAP_TYPE_SOCKMAP
 *
 * The socket map is a specialized map type which hold network sockets as
 * value.
 *
 * The value_size must always be 4 and the key_size must always be 8.
 */
struct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
} sock_map SEC(".maps");


SEC("sk_skb")
int prog_skb_drop(struct __sk_buff *skb)
{
	return SK_PASS;
}

char _license[] SEC("license") = "GPL";
