// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_KPROBE
 *
 * This program are eBPF programs that can attach to kprobes. KProbes are not
 * a eBPF specific feature, but they do work very well together. Traditionally,
 * one would have to write a custom kernel module which could be invoked from
 * a kprobe or be content with just the trace log output. eBPF makes this
 * process easier.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "bpf_misc.h"

#ifndef EINVAL
#define EINVAL 22
#endif

SEC("kprobe/"KSYM_DO_EXECVEAT_COMMON)
int BPF_KPROBE(do_execveat_common, int fd, struct filename *name)
{
	pid_t pid;
	const char *filename = NULL;
	pid = bpf_get_current_pid_tgid() >> 32;
	filename = BPF_CORE_READ(name, name);

/**
 * static long (* const bpf_override_return)(struct pt_regs *regs, __u64 rc) = (void *) 58;
 *
 * Used for error injection, this helper uses kprobes to override the return
 * value of the probed function, and to set it to rc. The first argument is
 * the context regs on which the kprobe works.
 *
 * This helper works by setting the PC (program counter) to an override function
 * which is run in place of the original probed function. This means the probed
 * function is not run at all. The replacement function just returns with the
 * required value.
 *
 * This helper has security implications, and thus is subject to restrictions.
 * It is only available if the kernel was compiled with the
 * CONFIG_BPF_KPROBE_OVERRIDE configuration option, and in this case it only
 * works on functions tagged with ALLOW_ERROR_INJECTION in the kernel code.
 */
#if defined(CONFIG_BPF_KPROBE_OVERRIDE)
#pragma message "Support bpf_override_return()"
	if (filename && str_eq(filename, "ls", 2)) {
		u64 err = EINVAL;
		bpf_override_return(ctx, err);
		bpf_printk("KPROBE ENTRY pid = %d, filename = %s override return",
			   pid, filename);
	}
#endif

/**
 * See also linux >= v6.6-rc2-737-g4ac454682158
 * commit 4ac454682158 ("bpf: Introduce task_vma open-coded iterator kfuncs")
 *
 * bpf_iter_task_vma_new()
 * bpf_iter_task_vma_next()
 * bpf_iter_task_vma_destroy()
 */
#if defined(SUPPORT_BPF_ITER_TASK_VMA_NEW)
	struct bpf_iter_task_vma vma_it;
	struct vm_area_struct *vma_ptr;
	struct task_struct *cur_task = bpf_get_current_task_btf();

	bpf_iter_task_vma_new(&vma_it, cur_task, 0);

	while ((vma_ptr = bpf_iter_task_vma_next(&vma_it))) {
		struct file *file = vma_ptr->vm_file;
		unsigned long i_ino = 0;
		if (file) {
			struct inode *ino = file->f_inode;
			i_ino = ino->i_ino;
		}
		bpf_printk("vma: %lx~%lx %ld", vma_ptr->vm_start, vma_ptr->vm_end, i_ino);
	}

	bpf_iter_task_vma_destroy(&vma_it);
#endif

	bpf_printk("KPROBE ENTRY pid = %d, filename = %s", pid, filename);
	return 0;
}

SEC("kretprobe/"KSYM_DO_EXECVEAT_COMMON)
int BPF_KRETPROBE(do_execveat_common_exit, long ret)
{
	pid_t pid;
	pid = bpf_get_current_pid_tgid() >> 32;
	bpf_printk("KPROBE EXIT: pid = %d, ret = %ld", pid, ret);

	#if defined(SUPPORT_BPF_STRNCMP)
	# if 1
	char s1[5] = {"test"};
	const static char s2[5] = {"test"};
	bpf_strncmp(s1, 5, s2);
	# else
	bpf_strncmp("top", 3, "topxxx");
	# endif
	#endif
	return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
