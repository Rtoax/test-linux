/**
 * BPF_PROG_TYPE_CGROUP_SOCK_ADDR
 *
 * cGroup socket address programs are triggered when a process in a cGroup to
 * which the program is attached uses socket related syscalls. This program can
 * overwrite arguments to the syscall such as addresses.
 *
 * This program type can be used to overwrite arguments to socket related
 * syscalls or to block the call to the syscall entirely. Which syscall depends
 * on the attach type used.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_endian.h>


/**
 * BPF_CGROUP_INET4_BIND v4.17
 */
SEC("cgroup/bind4")
int bind_v4_prog(struct bpf_sock_addr *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET6_BIND v4.17
 */
SEC("cgroup/bind6")
int bind_v6_prog(struct bpf_sock_addr *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET4_CONNECT v4.17
 */
SEC("cgroup/connect4")
int connect4(struct bpf_sock_addr *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET6_CONNECT v4.17
 */
SEC("cgroup/connect6")
int connect6(struct bpf_sock_addr *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_UDP4_SENDMSG and BPF_CGROUP_UDP6_SENDMSG v4.18
 * BPF_CGROUP_UDP4_RECVMSG and BPF_CGROUP_UDP6_RECVMSG v5.2
 */

/**
 * BPF_CGROUP_INET4_GETSOCKNAME v5.8
 */
SEC("cgroup/getsockname4")
int getsockname4(struct bpf_sock_addr *ctx)
{
	return 1;
}

/**
 * BPF_CGROUP_INET6_GETSOCKNAME v5.8
 */
SEC("cgroup/getpeername4")
int getpeername4(struct bpf_sock_addr *ctx)
{
	return 1;
}

char _license[] SEC("license") = "GPL";
