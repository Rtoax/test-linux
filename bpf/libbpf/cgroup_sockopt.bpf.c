/**
 * BPF_PROG_TYPE_CGROUP_SOCKOPT
 *
 * cGroup socket ops programs are executed when a process in the cGroup to
 * which the program is attached uses the getsockopt or setsockopt syscall
 * depending on the attach type and modify or block the operation.
 *
 * cGroup socket ops programs are typically located in the cgroup/getsockopt
 * or cgroup/setsockopt ELF section to indicate the BPF_CGROUP_GETSOCKOPT and
 * BPF_CGROUP_SETSOCKOPT attach types respectively.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>

SEC("cgroup/getsockopt")
int getsockopt(struct bpf_sockopt *ctx)
{
	return 1;
}

SEC("cgroup/setsockopt")
int setsockopt(struct bpf_sockopt *ctx)
{
	return 1;
}

char _license[] SEC("license") = "GPL";
