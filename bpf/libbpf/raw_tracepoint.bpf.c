/**
 * BPF_PROG_TYPE_RAW_TRACEPOINT
 */
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

/**
 * struct bpf_raw_tracepoint_args {
 *	__u64 args[0];
 * };
 */

#if defined(SEC_DEF_RAW_TRACEPOINT)
SEC("raw_tracepoint/sched_process_fork")
#elif defined(SEC_DEF_RAW_TP)
SEC("raw_tp/sched_process_fork")
#else
# error "Not define SEC_DEF_RAW_TRACEPOINT or SEC_DEF_RAW_TP"
#endif
int bpf_sched_process_fork(struct bpf_raw_tracepoint_args *ctx)
{
	struct data_t data = {};
	u64 uid;
	struct task_struct *parent, *child;

	parent = (struct task_struct *)ctx->args[0];
	child = (struct task_struct *)ctx->args[1];

	data.pid = bpf_get_current_pid_tgid();
	uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
	data.uid = uid;

	/**
	 * TP_PROTO(struct task_struct *parent, struct task_struct *child)
	 */
	bpf_core_read(&data.parent_comm, sizeof(data.parent_comm), (void *)parent->comm);
	bpf_core_read(&data.child_comm, sizeof(data.child_comm), (void *)child->comm);
	bpf_get_current_comm(&data.comm, sizeof(data.comm));

	bpf_perf_event_output(ctx, &event, BPF_F_CURRENT_CPU,  &data, sizeof(data));
	return 0;
}

char LICENSE[] SEC("license") = "GPL";
