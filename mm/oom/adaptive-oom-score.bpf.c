// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "adaptive-oom-score.h"


#if defined(DEBUG)
#define BPF_DEBUG(fmt...) bpf_printk(fmt)
#else
#pragma message("You could $ make DEBUG=1 to enable debug info")
#define BPF_DEBUG(fmt...)
#endif

struct {
	__uint(type, BPF_MAP_TYPE_RINGBUF);
	__uint(max_entries, 4096 * 64);
} ring_buf SEC(".maps");


#if defined(__TARGET_ARCH_x86)
SEC("tracepoint/exceptions/page_fault_user")
int tracepoint__pf_user(struct trace_event_raw_x86_exceptions *ctx)
#else
#error "Only support x86_64 yet"
#endif
{
	BPF_DEBUG("Start");

	struct pf_event_t *pf_ev;
	pid_t pid = (pid_t)(bpf_get_current_pid_tgid() >> 32);

	pf_ev = bpf_ringbuf_reserve(&ring_buf, sizeof(*pf_ev), 0);
	if (!pf_ev)
		return 0;

	BPF_DEBUG("Reserve from ring buffer");

	pf_ev->pid = pid;
	pf_ev->error_code = ctx->error_code;

	BPF_DEBUG("Submit");

	bpf_ringbuf_submit(pf_ev, 0);
	return 0;
}

char __license[] SEC("license") = "GPL";
