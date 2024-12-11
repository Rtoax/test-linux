#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "raw_tracepoint.h"

struct {
	__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uint(key_size, sizeof(u32));
	__uint(value_size, sizeof(u32));
} event SEC(".maps");

SEC("raw_tracepoint/sys_enter")
int raw_tp_sys_enter(void *ctx)
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

char LICENSE[] SEC("license") = "GPL";
