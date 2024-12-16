// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2024 Rong Tao */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "iter.h"

static __u32 zero = 0;

#if defined(ITER_BPF_MAP)
struct {
	__uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct iter_bpf_map_info);
} bpf_map_info_buf SEC(".maps");

SEC("iter/bpf_map")
int dump_bpf_map(struct bpf_iter__bpf_map *ctx)
{
	struct seq_file *seq = ctx->meta->seq;
	struct bpf_map *map = ctx->map;
	struct iter_bpf_map_info *t;
	u64 pid_tgid;

	if (map == (void *)0)
		return 0;

	t = bpf_map_lookup_elem(&bpf_map_info_buf, &zero);
	if (!t)
		return 0;

	pid_tgid = bpf_get_current_pid_tgid() >> 32;

	t->pid = pid_tgid >> 32;
	t->tid = pid_tgid & 0xFFFFFFFF;
	bpf_get_current_comm(&t->comm, sizeof(t->comm));

	t->map_type = map->map_type;
	t->map_id = map->id;

	bpf_seq_write(seq, t, sizeof(struct task_file_info));
	return 0;
}
#endif

char _license[] SEC("license") = "GPL";
