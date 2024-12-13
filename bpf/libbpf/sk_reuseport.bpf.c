/**
 * BPF_PROG_TYPE_SK_REUSEPORT
 *
 * Socket reuse port programs can be attached to a SO_REUSEPORT socket group
 * to replace the default socket selection mechanism.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("sk_reuseport")
int reuseport_pass(struct sk_reuseport_md *ctx)
{
	return SK_PASS;
}

SEC("sk_reuseport")
int reuseport_drop(struct sk_reuseport_md *ctx)
{
	return SK_DROP;
}

char _license[] SEC("license") = "GPL";
