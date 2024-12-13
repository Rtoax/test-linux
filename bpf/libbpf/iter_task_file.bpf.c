// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2024 Rong Tao */
/* Copyright (c) 2020 Facebook */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "iter_task.h"

struct {
	__uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct task_info);
} task_file_info_buf SEC(".maps");

static __u32 zero = 0;

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

char _license[] SEC("license") = "GPL";
