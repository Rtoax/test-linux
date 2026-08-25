/**
 * static long (*const bpf_perf_event_output)(void *ctx, void *map, __u64 flags,
 *                                            void *data, __u64 size);
 * BPF_FUNC_perf_event_output = (void *) 25;
 * linux >= v4.4
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_perf_event_output/
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

struct {
	__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uint(key_size, sizeof(u32));
	__uint(value_size, sizeof(u32));
} events SEC(".maps");

void test(void *ctx)
{
	int event = 1024;
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, &event,
			      sizeof(event));
}
