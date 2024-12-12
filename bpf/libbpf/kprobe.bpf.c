// SPDX-License-Identifier: GPL-3.0
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("kprobe/"KSYM_DO_EXECVEAT_COMMON)
int BPF_KPROBE(do_execveat_common, int fd, struct filename *name)
{
	pid_t pid;
	const char *filename;
	pid = bpf_get_current_pid_tgid() >> 32;
	filename = BPF_CORE_READ(name, name);
	bpf_printk("KPROBE ENTRY pid = %d, filename = %s", pid, filename);
	return 0;
}

SEC("kretprobe/"KSYM_DO_EXECVEAT_COMMON)
int BPF_KRETPROBE(do_execveat_common_exit, long ret)
{
	pid_t pid;
	pid = bpf_get_current_pid_tgid() >> 32;
	bpf_printk("KPROBE EXIT: pid = %d, ret = %ld", pid, ret);
	return 0;
}
