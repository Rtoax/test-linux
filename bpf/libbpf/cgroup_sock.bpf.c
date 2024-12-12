/**
 * BPF_PROG_TYPE_CGROUP_SOCK
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>


SEC("cgroup/sock_create")
int sock_create(struct bpf_sock *ctx)
{
	return 1;
}

SEC("cgroup/sock_release")
int sock_release(struct bpf_sock *ctx)
{
	return 1;
}

SEC("cgroup/sock")
int sock(struct bpf_sock *ctx)
{
	return 1;
}

SEC("cgroup/post_bind4")
int post_bind4(struct bpf_sock *ctx)
{
	return 1;
}

SEC("cgroup/post_bind5")
int post_bind5(struct bpf_sock *ctx)
{
	return 1;
}

char _license[] SEC("license") = "GPL";
