#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

/* SEC("socketxxxx") will be parse as BPF_PROG_TYPE_SOCKET_FILTER */
SEC("socket_filter")
int bpf_prog1(struct __sk_buff *ctx)
{
	return 0;
}
char __license[] SEC("license") = "GPL";
