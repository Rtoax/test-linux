/**
 * BPF_PROG_TYPE_TRACING
 *
 * Tracing programs are a newer alternative to kprobes and tracepoints. Tracing
 * programs utilize BPF trampolines, a new mechanism which provides practically
 * zero overhead. In addition, tracing programs can be attached to BPF programs
 * to provide troubleshooting and debugging capabilities, something that is not
 * possible with kprobes.
 *
 * v5.8: Iterator
 * v5.7: Modify return
 * v5.5: Raw tracepoint, Fentry, Fexit
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

/* See bcc tools/opensnoop.py */
SEC("fentry/" SYS_PREFIX "sys_openat")
#if defined(CONFIG_ARCH_HAS_SYSCALL_WRAPPER)
int BPF_PROG(test_sys_openat, struct pt_regs *regs)
{
	int dfd = PT_REGS_PARM1(regs);
	const char *filename = (const char *)PT_REGS_PARM2(regs);
	int flags = PT_REGS_PARM3(regs);
	umode_t mode = PT_REGS_PARM4(regs);
#else
int BPF_PROG(test_sys_openat, int dfd, const char *filename, int flags,
	     unsigned short mode)
{
#endif
	bpf_printk("openat(%d, %s, %08o, ", dfd, filename, flags);
	bpf_printk("%04o)", mode);
	return 0;
}

char _license[] SEC("license") = "GPL";
