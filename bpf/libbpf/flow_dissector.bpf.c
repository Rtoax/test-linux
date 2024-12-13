/**
 * BPF_PROG_TYPE_FLOW_DISSECTOR
 *
 * Flow dissector is a program type that parses metadata out of the packets.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>


SEC("flow_dissector")
int _dissect(struct __sk_buff *skb)
{
	return BPF_DROP;
}

char _license[] SEC("license") = "GPL";
