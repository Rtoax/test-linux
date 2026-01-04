// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * long bpf_get_stackid(void *ctx, struct bpf_map *map, u64 flags);
 *
 * Walk a user or a kernel stack and return its id. To achieve this, the helper
 * needs ctx, which is a pointer to the context on which the tracing program is
 * executed, and a pointer to a map of type.
 *
 * Program types:
 * - BPF_PROG_TYPE_KPROBE
 * - BPF_PROG_TYPE_PERF_EVENT
 * - BPF_PROG_TYPE_RAW_TRACEPOINT
 * - BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE
 * - BPF_PROG_TYPE_TRACEPOINT
 * - BPF_PROG_TYPE_TRACING
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_get_stackid/
 */
#pragma once
#include "stack_helpers.h"

struct {
	__uint(type, BPF_MAP_TYPE_STACK_TRACE);
	__uint(max_entries, 1024);
	__type(key, __u32);
	__type(value, sizeof(unsigned long) * STACK_MAX_DEPTH);
} stackmap SEC(".maps");

void __get_stack(void *ctx)
{
	int user_stack_id;
	int kern_stack_id;

	/* Walk a kernel stack and return its id. */
	kern_stack_id = bpf_get_stackid(ctx, &stackmap, 0);
	/* Collect a user space stack instead of a kernel stack. */
	user_stack_id = bpf_get_stackid(ctx, &stackmap, BPF_F_USER_STACK);

	if (kern_stack_id >= 0 && user_stack_id >= 0) {
		bpf_printk("Stack kernel %d, user %d", kern_stack_id, user_stack_id);
	}
}
