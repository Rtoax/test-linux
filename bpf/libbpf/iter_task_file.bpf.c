// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2024 Rong Tao */
/* Copyright (c) 2020 Facebook */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "iter.h"

static __u32 zero = 0;

#if defined(ITER_TASK_FILE)
struct {
	__uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct task_file_info);
} task_file_info_buf SEC(".maps");

SEC("iter/task_file")
int dump_task_file(struct bpf_iter__task_file *ctx)
{
	struct seq_file *seq = ctx->meta->seq;
	struct task_struct *task = ctx->task;
	struct file *file = ctx->file;
	__u32 fd = ctx->fd;
	struct task_file_info *t;

	if (task == (void *)0 || file == (void *)0)
		return 0;

	t = bpf_map_lookup_elem(&task_file_info_buf, &zero);
	if (!t)
		return 0;

	t->pid = task->tgid;
	t->tid = task->pid;
	t->fd = fd;
	bpf_probe_read_kernel_str(t->comm, TASK_COMM_LEN, task->comm);

	bpf_seq_write(seq, t, sizeof(struct task_file_info));
	return 0;
}
#elif defined(ITER_TASK_VMA)
struct {
	__uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct task_vma_info);
} task_vma_info_buf SEC(".maps");

SEC("iter/task_vma")
int dump_task_vma(struct bpf_iter__task_vma *ctx)
{
	struct seq_file *seq = ctx->meta->seq;
	struct task_struct *task = ctx->task;
	struct vm_area_struct *vma = ctx->vma;
	struct task_vma_info *t;

	if (task == (void *)0 || vma == (void *)0)
		return 0;

	t = bpf_map_lookup_elem(&task_vma_info_buf, &zero);
	if (!t)
		return 0;

	t->pid = task->tgid;
	t->tid = task->pid;
	bpf_probe_read_kernel_str(t->comm, TASK_COMM_LEN, task->comm);
	t->vm_start = vma->vm_start;
	t->vm_end = vma->vm_end;

	bpf_seq_write(seq, t, sizeof(struct task_vma_info));
	return 0;
}
#endif

char _license[] SEC("license") = "GPL";
