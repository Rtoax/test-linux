/**
 * static long (*const bpf_send_signal)(__u32 sig) = (void *)109;
 *
 * Program types:
 * - BPF_PROG_TYPE_KPROBE
 * - BPF_PROG_TYPE_LSM
 * - BPF_PROG_TYPE_PERF_EVENT
 * - BPF_PROG_TYPE_RAW_TRACEPOINT
 * - BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE
 * - BPF_PROG_TYPE_SYSCALL
 * - BPF_PROG_TYPE_TRACEPOINT
 * - BPF_PROG_TYPE_TRACING
 *
 * Refs:
 * - linux v5.2-rc1-220-g8b401f9ed244
 *   commit 8b401f9ed244 ("bpf: implement bpf_send_signal() helper")
 * - https://docs.ebpf.io/linux/helper-function/bpf_send_signal/
 */
#include "vmlinux.h"

void test(void)
{
	bpf_send_signal(2 /* SIGINT */);
}
