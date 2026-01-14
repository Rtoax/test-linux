/**
 * linux commit 3f0e6f2b41d3 ("bpf: Add bpf_task_from_pid() kfunc")
 * v6.1-rc4-1163-g3f0e6f2b41d3
 *
 * linux commit bc638d8cb5be ("bpf: allow kfuncs within tracepoint and perf event programs")
 * v6.11-rc4-276-gbc638d8cb5be
 *
 * or use CO-RE method https://github.com/iovisor/bcc/pull/5272
 */
#include "vmlinux.h"

extern struct task_struct *bpf_task_from_pid(s32 pid) __weak __ksym;
extern void bpf_task_release(struct task_struct *p) __weak __ksym;

void test(void)
{
	pid_t pid = 7;
	struct task_struct *task = bpf_task_from_pid(pid);
	if (task) {
		bpf_task_release(task);
	}
}
