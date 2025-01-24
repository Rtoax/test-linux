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
#include "bpf_debug.h"

#define NANOSLEEP	1
#define OPENAT		1

#ifdef NANOSLEEP
struct nanosleep_args {
	struct timespec64 duration;
	struct timespec64 rem;
};

SEC("fentry/" SYS_PREFIX "sys_nanosleep")
#if defined(CONFIG_ARCH_HAS_SYSCALL_WRAPPER)
int BPF_PROG(test_sys_nanosleep, struct pt_regs *regs)
{
#if 0
	/**
	 * ; bpf_printk("nanosleep({.tv_sec = %ld, .tv_nsec = %ld})",
	 * 2: (79) r4 = *(u64 *)(r1 +8)
	 * R1 invalid mem access 'inv'
	 */
	struct timespec64 *duration = (void *)PT_REGS_PARM1(regs);
#else
	struct nanosleep_args args = {};
	struct timespec64 *duration = (void *)PT_REGS_PARM1(regs);

	if (bpf_probe_read(&args.duration, sizeof(struct timespec64), duration))
		return 0;

	duration = &args.duration;
#endif
#else
int BPF_PROG(test_sys_nanosleep, const struct timespec64 *duration,
	     struct timespec64 *rem)
{
#endif
	bpf_printk("nanosleep({.tv_sec = %ld, .tv_nsec = %ld})",
		   duration->tv_sec, duration->tv_nsec);
	return 0;
}

SEC("fexit/" SYS_PREFIX "sys_nanosleep")
#if defined(CONFIG_ARCH_HAS_SYSCALL_WRAPPER)
int BPF_PROG(test_sys_nanosleep_ret, struct pt_regs *regs, int ret)
{
	struct nanosleep_args args = {};
	struct timespec64 *duration = (void *)PT_REGS_PARM1(regs);

	if (bpf_probe_read(&args.duration, sizeof(struct timespec64), duration))
		return 0;

	duration = &args.duration;
#else
int BPF_PROG(test_sys_nanosleep_ret, const struct timespec64 *duration,
	     struct timespec64 *rem, int ret)
{
#endif
	bpf_printk("nanosleep({.tv_sec = %ld, .tv_nsec = %ld}) = %d",
		   duration->tv_sec, duration->tv_nsec, ret);
	return 0;
}
#endif // NANOSLEEP

struct openat_args {
	int dfd;
	char filename[256];
	int flags;
	umode_t mode;
};

#ifdef OPENAT
/* See bcc tools/opensnoop.py */
SEC("fentry/" SYS_PREFIX "sys_openat")
#if defined(CONFIG_ARCH_HAS_SYSCALL_WRAPPER)
int BPF_PROG(test_sys_openat, struct pt_regs *regs)
{
	int dfd = (int)PT_REGS_PARM1(regs);
	const char *filename = (const char *)PT_REGS_PARM2(regs);
	int flags = (int)PT_REGS_PARM3(regs);
	umode_t mode = 0;

#ifndef O_CREAT
#define O_CREAT		00000100
#endif
	/**
	 * The mode parameter is only present when the flags parameter includes
	 * the O_CREAT flag. This means that the mode parameter is the fourth
	 * argument, but you should only access it if the third parameter
	 * flags includes O_CREAT.
	 */
	if (flags & O_CREAT) {
		mode = (umode_t)PT_REGS_PARM4(regs);
		BPF_DEBUG("O_CREAT %s mode = 0x%x", filename, mode);
	}

/**
 * Actually, no need to use bpf_probe_read() here.
 */
#ifdef use_bpf_probe_read
	struct openat_args args = {};

	if (bpf_probe_read_str(args.filename, sizeof(args.filename), filename) <= 0)
		return 0;
	filename = args.filename;
	BPF_DEBUG("filename = %s", filename);

	if (bpf_probe_read(&args.flags, sizeof(args.flags), &flags))
		return 0;
	flags = args.flags;
	BPF_DEBUG("flags = %x", flags);

	if (bpf_probe_read(&args.mode, sizeof(args.mode), &mode))
		return 0;
	mode = args.mode;
	BPF_DEBUG("mode = %04o", mode);
#endif

#else /* CONFIG_ARCH_HAS_SYSCALL_WRAPPER */

int BPF_PROG(test_sys_openat, int dfd, const char *filename, int flags,
	     unsigned short mode)
{
#endif
	bpf_printk("openat(%d, %s, %08x, ", dfd, filename, flags);
	/**
	 * FIXME: bpf_printk() could not print octal with %o, print nothing if
	 * use %o instead of %x.
	 */
	bpf_printk("                     mode = 0x%x)", mode);
	return 0;
}
#endif

char _license[] SEC("license") = "GPL";
