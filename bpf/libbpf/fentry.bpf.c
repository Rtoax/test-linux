/**
 * BPF_PROG_TYPE_TRACING fentry
 */
#include <vmlinux.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_helpers.h>
#include "bpf_misc.h"

#define WITH_PARAMS

SEC("fentry/" SYS_PREFIX "sys_nanosleep")
#if defined(WITH_PARAMS)
int BPF_PROG(test_sys_nanosleep, const struct timespec64 *duration,
	     struct timespec64 *rem)
#else
int test_sys_nanosleep(void *ctx)
#endif
{
#if defined(WITH_PARAMS)
	bpf_printk("nanosleep({.tv_sec = %ld, .tv_nsec = %ld})",
		   duration->tv_sec, duration->tv_nsec);
#else
	bpf_printk("nanosleep(?)");
#endif
	return 0;
}

char _license[] SEC("license") = "GPL";
