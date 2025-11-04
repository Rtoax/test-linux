// SPDX-License-Identifier: GPL-3.0
#include "vmlinux.h"
#include <linux/version.h>

int task_comm_from_pid(int pid, char *comm, size_t size)
{
/**
 * linux commit 3f0e6f2b41d3 ("bpf: Add bpf_task_from_pid() kfunc")
 * v6.1-rc4-1163-g3f0e6f2b41d3
 *
 * linux commit bc638d8cb5be ("bpf: allow kfuncs within tracepoint and perf event programs")
 * v6.11-rc4-276-gbc638d8cb5be
 *
 * or use CO-RE method https://github.com/iovisor/bcc/pull/5272
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
	if (bpf_ksym_exists(bpf_task_from_pid)) {
		/**
		 * struct task_struct *bpf_task_from_pid(s32 pid)
		 */
		struct task_struct *task = bpf_task_from_pid(pid);
		if (task) {
			bpf_probe_read_kernel(comm, size, task->comm);
			/**
			 * void bpf_task_release(struct task_struct *p)
			 */
			bpf_task_release(task);
		}
	}
#else
	comm[0] = 'N';
	comm[1] = '/';
	comm[2] = 'A';
	comm[3] = '?';
	comm[4] = '0' + LINUX_VERSION_MAJOR;
	comm[5] = '\0';
#endif
	return 0;
}
