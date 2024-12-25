/**
 * BPF_MAP_TYPE_STACK
 *
 * The stack map type is a generic map type, resembling a stack data structure.
 *
 * This map type has no keys, only values. The size and type of the values can
 * be specified by the user to fit a large variety of use cases. The typical
 * use-case for this map type is for brace matching ({,}) when parsing JSON for
 * example.
 *
 * As apposed to most map types, this map type uses a custom set of helpers to
 * pop, peek and push elements, noted in the helper functions section below.
 */

#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define MAX_ENTRIES	1024

struct {
	__uint(type, BPF_MAP_TYPE_STACK);
	__uint(max_entries, MAX_ENTRIES);
	__type(value, __u32);
} m_stack SEC(".maps");

char LICENSE[] SEC("license") = "Dual BSD/GPL";
