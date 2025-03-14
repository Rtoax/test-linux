/**
 * BPF_MAP_TYPE_LPM_TRIE
 *
 * The LPM (Largest Prefix Match) map is a generic map type which does prefix
 * matching on the key upon lookup.
 *
 * One of the main use cases for this map type is to implement routing tables
 * or policies for IP ranges. Take the following key-value pairs:
 *
 *   10.0.0.0/8 -> 1
 *   10.0.10.0/24 -> 2
 *   10.0.10.123/32 -> 3
 *
 * A lookup for 10.0.10.123 will return value 3 because we have a specific
 * entry for it in the map. A lookup for 10.0.10.200 will return value 2,
 * because the /24 key is more specific than the /8 key. A lookup for
 * 10.12.0.1 would return 1. And a lookup for 12.0.0.1 will not return any
 * entry.
 *
 * kernel commit b95a5c4db09b ("bpf: add a longest prefix match trie map implementation")
 * v4.10-rc4-728-gb95a5c4db09b introduce BPF_MAP_TYPE_LPM_TRIE.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "bpf_misc.h"

struct {
	__uint(type, BPF_MAP_TYPE_LPM_TRIE);
	__uint(max_entries, 16);
	__uint(key_size, sizeof(u32));
	__uint(value_size, sizeof(u32));
	__uint(map_flags, BPF_F_NO_PREALLOC);
} lpm_val_map SEC(".maps");


char LICENSE[] SEC("license") = "Dual BSD/GPL";
