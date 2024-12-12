/**
 * BPF_PROG_TYPE_TRACEPOINT
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "tracepoint.h"

struct {
	__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uint(key_size, sizeof(u32));
	__uint(value_size, sizeof(u32));
} event SEC(".maps");

#if defined(SEC_DEF_TRACEPOINT)
SEC("tracepoint/syscalls/sys_enter_execve")
#elif defined(SEC_DEF_TP)
SEC("tp/syscalls/sys_enter_execve")
#else
# error "Not define SEC_DEF_TRACEPOINT or SEC_DEF_TP"
#endif
int tracepoint__syscalls__sys_enter_execve(struct syscall_trace_enter* ctx)
{
	struct data_t data = {};
	u64 uid;

	data.pid = bpf_get_current_pid_tgid();
	uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
	data.uid = uid;

	bpf_get_current_comm(&data.command, sizeof(data.command));
	bpf_perf_event_output(ctx, &event, BPF_F_CURRENT_CPU,  &data, sizeof(data));

	return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
