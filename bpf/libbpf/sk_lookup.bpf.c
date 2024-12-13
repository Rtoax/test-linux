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
#include <bpf/bpf_core_read.h>

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

/**
 * linux commit f89315650ba3 ("bpf: Add ingress_ifindex to bpf_sk_lookup") add
 * field ingress_ifindex in v5.15-4621-gf89315650ba3.
 */
struct bpf_sk_lookup___x {
	__u32 ingress_ifindex;
} __attribute__((preserve_access_index));

static __always_inline bool bpf_sk_lookup_has_ingress_ifindex_field(void)
{
	if (bpf_core_field_exists(((struct bpf_sk_lookup___x *)0)->ingress_ifindex))
		return true;
	return false;
}

static __always_inline __u32 load_ingress_ifindex(struct bpf_sk_lookup *ctx)
{
	__u32 index;
	void *p = ctx;
	int sz;
	off_t off;

	if (bpf_sk_lookup_has_ingress_ifindex_field()) {
		sz = bpf_core_field_size(((struct bpf_sk_lookup *)0)->local_port);
		off = (off_t)(((struct bpf_sk_lookup *)0)->local_port);
		index = *(__u32 *)(p + off + sz);
	} else
		index = 0xFFFF;

	return index;
}

SEC("sk_lookup")
int check_ifindex(struct bpf_sk_lookup *ctx)
{
	__u32 ingress_ifindex = load_ingress_ifindex(ctx);

	if (ingress_ifindex != 0xFFFF && ingress_ifindex == 1)
		return SK_DROP;
	return SK_PASS;
}

char _license[] SEC("license") = "GPL";
