/**
 * BPF_PROG_TYPE_SOCK_OPS
 */
#include <vmlinux.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

SEC("sockops")
int _sockops(struct bpf_sock_ops *ctx)
{
	/* TODO */
	return 0;
}

char __license[] SEC("license") = "GPL";
