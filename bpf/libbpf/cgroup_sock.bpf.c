/**
 * BPF_PROG_TYPE_CGROUP_SOCK
 *
 * cGroup socket programs are attached to cGroups and triggered when sockets
 * are created, released or bound by a process in the cGroup.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>


/**
 * BPF_CGROUP_INET_SOCK_CREATE
 */
SEC("cgroup/sock_create")
int sock_create(struct bpf_sock *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET_SOCK_RELEASE
 */
SEC("cgroup/sock_release")
int sock_release(struct bpf_sock *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET_SOCK_CREATE
 */
SEC("cgroup/sock")
int sock(struct bpf_sock *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET4_POST_BIND
 */
SEC("cgroup/post_bind4")
int post_bind4(struct bpf_sock *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET6_POST_BIND
 */
SEC("cgroup/post_bind6")
int post_bind6(struct bpf_sock *ctx)
{
	return 1;
}

char _license[] SEC("license") = "GPL";
