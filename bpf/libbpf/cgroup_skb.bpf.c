/**
 * BPF_PROG_TYPE_CGROUP_SKB
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
