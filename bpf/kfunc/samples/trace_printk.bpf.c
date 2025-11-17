/**
 * int bpf_trace_printk(const char *fmt, int fmt_size, ...);
 * BPF_FUNC_trace_printk = 6
 *
 * linux v4.0-rc5-419-g9c959c863f82
 * commit 9c959c863f82 ("tracing: Allow BPF programs to call bpf_trace_printk()")
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_trace_printk/
 */
#include "vmlinux.h"

void test(void)
{
	char s1[] = "Hello, World!";
	bpf_trace_printk(s1, 15);
}
