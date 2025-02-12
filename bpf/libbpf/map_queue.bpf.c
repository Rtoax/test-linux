/**
 * BPF_MAP_TYPE_QUEUE
 *
 * The queue map type is a generic map type, resembling a FIFO (First-In
 * First-Out) queue.
 *
 * his map type has no keys, only values. The size and type of the values can
 * be specified by the user to fit a large variety of use cases. The typical
 * use-case for this map type is to keep track of a pool of elements such as
 * available network ports when implementing NAT (network address translation).
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define MAX_ENTRIES	1024

struct {
	/* bpf_attr::key_size must be 0 */
	__uint(type, BPF_MAP_TYPE_QUEUE);
	__uint(max_entries, MAX_ENTRIES);
	__type(value, __u32);
} map_queue SEC(".maps");

char LICENSE[] SEC("license") = "Dual BSD/GPL";
