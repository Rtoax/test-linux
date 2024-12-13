/**
 * BPF_PROG_TYPE_TRACING fentry
 */
#include <vmlinux.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_helpers.h>
#include "bpf_misc.h"

#define WITH_PARAMS 1

SEC("fentry/" SYS_PREFIX "sys_nanosleep")
#if WITH_PARAMS == 1
int BPF_PROG(test_sys_nanosleep, const struct timespec64 *duration,
	     struct timespec64 *rem)
#else
int test_sys_nanosleep(void *ctx)
#endif
{
#if WITH_PARAMS == 1
	bpf_printk("nanosleep({.tv_sec = %ld, .tv_nsec = %ld})",
		   duration->tv_sec, duration->tv_nsec);
#else
	bpf_printk("nanosleep(?)");
#endif
	return 0;
}

SEC("fexit/" SYS_PREFIX "sys_nanosleep")
#if WITH_PARAMS == 1
/**
 * FIXME: Why not the following!!
 * int BPF_PROG(test_sys_nanosleep_ret, const struct timespec64 *duration,
 *		struct timespec64 *rem, int ret)
 */
int BPF_PROG(test_sys_nanosleep_ret, struct pt_regs *regs, int ret)
#else
int test_sys_nanosleep_ret(void *ctx)
#endif
{
#if WITH_PARAMS == 1
	bpf_printk("nanosleep(?) ret = %d", ret);
#else
	bpf_printk("nanosleep(?) ret");
#endif
	return 0;
}

SEC("fexit/" SYS_PREFIX "sys_openat2")
int BPF_PROG(test_sys_openat2_ret, struct pt_regs *regs, int ret)
{
	bpf_printk("openat2(?) ret = %d", ret);
	return 0;
}

char _license[] SEC("license") = "GPL";
