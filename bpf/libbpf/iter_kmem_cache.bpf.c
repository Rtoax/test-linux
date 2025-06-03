// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "iter.h"

struct {
	__uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uint(max_entries, 1);
	__type(key, __u32);
	__type(value, struct iter_kmem_cache_info);
} kmem_cache_info_buf SEC(".maps");

static __u32 zero = 0;

SEC("iter/kmem_cache")
int dump_kmem_cache(struct bpf_iter__kmem_cache *ctx)
{
	struct seq_file *seq = ctx->meta->seq;
	struct kmem_cache *s = ctx->s;
	struct iter_kmem_cache_info *info;

	if (!s)
		return 0;

	info = bpf_map_lookup_elem(&kmem_cache_info_buf, &zero);
	if (!info)
		return 0;

	/* TODO: add more kmem_cache info */

	bpf_probe_read_kernel_str(info->name, sizeof(info->name), s->name);
	info->size = s->size;

	bpf_seq_write(seq, info, sizeof(struct iter_kmem_cache_info));
	return 0;
}

char _license[] SEC("license") = "GPL";
