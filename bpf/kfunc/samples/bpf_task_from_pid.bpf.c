#include "vmlinux.h"

void test(pid_t pid)
{
	struct task_struct *task = bpf_task_from_pid(pid);
	if (task) {
		bpf_task_release(task);
	}
}
