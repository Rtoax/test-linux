/**
 * BPF_PROG_TYPE_SK_LOOKUP
 *
 * The socket lookup program allows an eBPF program to pick which socket to
 * send traffic to irrespective of how that target socket has been bound.
 *
 * The primary use case for this program type is to allow a single program
 * to handle traffic for network patterns which cannot be expressed with the
 * normal bind syscall. For example, a single socket can be bound to a whole
 * '/24' network CIDR (bind only allows for single IPs, or you have to set it
 * to 0.0.0.0 which is not desirable if another application should answer a
 * different range of IPs). Or a single socket can listen to any port for a
 * given IP.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("sk_lookup")
int lookup_pass(struct bpf_sk_lookup *ctx)
{
	return SK_PASS;
}

SEC("sk_lookup")
int lookup_drop(struct bpf_sk_lookup *ctx)
{
	return SK_DROP;
}

SEC("sk_lookup")
int check_ifindex(struct bpf_sk_lookup *ctx)
{
	if (ctx->ingress_ifindex == 1)
		return SK_DROP;
	return SK_PASS;
}

char _license[] SEC("license") = "GPL";
