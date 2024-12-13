/**
 * BPF_PROG_TYPE_CGROUP_SKB
 *
 * cGroup socket buffer programs are attached to a cGroup and are called for
 * incoming or outgoing packets to or from processes within that cGroup.
 * The programs can filter packets but not modify them.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>

SEC("cgroup/skb")
int bpf_nextcnt(struct __sk_buff *skb)
{
	return 0;
}

char _license[] SEC("license") = "GPL";
