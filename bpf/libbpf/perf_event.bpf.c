// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_PERF_EVENT
 *
 * Perf event programs that can be attached to hardware and software perf
 * events. Once attached the BPF program is executed each time the perf event
 * is triggered.
 *
 * Perf event programs are typically used for profiling and tracing. These
 * programs are called with the CPU register state at the time of the event.
 * This allows the programs to collect information for each event and aggregate
 * it in a customized way.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "perf_event.h"
#include "bpf_misc.h"


struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, u64);
	__type(value, u32);
	__uint(max_entries, MAX_IPS);
} vaddr_map SEC(".maps");

SEC("perf_event")
int do_sample(struct bpf_perf_event_data *ctx)
{
	u64 ip;
	u32 *value, init_val = 1;

	ip = PT_REGS_IP(&ctx->regs);
	value = bpf_map_lookup_elem(&vaddr_map, &ip);
	if (value) {
		*value += 1;
		if (*value % 100 == 0)
			bpf_printk("IP %#016lx sample %ld\n", ip, *value);
	} else
		/* E2BIG not tested for this example only */
		bpf_map_update_elem(&vaddr_map, &ip, &init_val, BPF_NOEXIST);

	return 0;
}

char _license[] SEC("license") = "GPL";
