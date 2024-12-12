// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_PERF_EVENT
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "perf_event.h"


struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, u64);
	__type(value, u32);
	__uint(max_entries, MAX_IPS);
} ip_map SEC(".maps");

SEC("perf_event")
int do_sample(struct bpf_perf_event_data *ctx)
{
	u64 ip;
	u32 *value, init_val = 1;

	ip = PT_REGS_IP(&ctx->regs);
	value = bpf_map_lookup_elem(&ip_map, &ip);
	if (value)
		*value += 1;
	else
		/* E2BIG not tested for this example only */
		bpf_map_update_elem(&ip_map, &ip, &init_val, BPF_NOEXIST);

	return 0;
}
char _license[] SEC("license") = "GPL";
