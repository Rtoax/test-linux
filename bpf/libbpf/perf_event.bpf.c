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

#define STACK_MAP	1
#if defined(STACK_MAP)
struct {
	__uint(type, BPF_MAP_TYPE_STACK_TRACE);
	__type(key, u32);
} stackmap SEC(".maps");
#endif


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
			bpf_printk("IP 0x%lx sample %ld", ip, *value);
	} else
		/* E2BIG not tested for this example only */
		bpf_map_update_elem(&vaddr_map, &ip, &init_val, BPF_NOEXIST);

#if defined(STACK_MAP)
	int user_stack_id;
	int kern_stack_id;
	/* Walk a kernel stack and return its id. */
	kern_stack_id = bpf_get_stackid(&ctx->regs, &stackmap, 0);
	/* Collect a user space stack instead of a kernel stack. */
	user_stack_id = bpf_get_stackid(&ctx->regs, &stackmap, BPF_F_USER_STACK);

	if (kern_stack_id >= 0 && user_stack_id >= 0) {
		bpf_printk("Stack kernel %d, user %d", kern_stack_id, user_stack_id);
	}
#endif
	return 0;
}

char _license[] SEC("license") = "GPL";
