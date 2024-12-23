/**
 * BPF_PROG_TYPE_TRACEPOINT
 *
 * This programs are eBPF programs that attach to pre-defined trace points in
 * the linux kernel. These tracepoint are often placed in locations which are
 * interesting or common locations to measure performance.
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "tracepoint.h"

struct {
#if defined(PERCPU_HASH)
	__uint(type, BPF_MAP_TYPE_PERCPU_HASH);
#else
	__uint(type, BPF_MAP_TYPE_HASH);
#endif
	__type(key, pid_t);
	__type(value, struct event_t);
	__uint(max_entries, MAX_ENTRIES);
} execs SEC(".maps");

struct {
	__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uint(key_size, sizeof(u32));
	__uint(value_size, sizeof(u32));
} events SEC(".maps");

static const struct event_t zero_event = {};

/**
 * struct syscall_trace_enter {
 * 	struct trace_entry	ent;
 * 	int			nr;
 * 	unsigned long		args[];
 * };
 */

#if defined(SEC_DEF_TRACEPOINT)
SEC("tracepoint/syscalls/sys_enter_execve")
#elif defined(SEC_DEF_TP)
SEC("tp/syscalls/sys_enter_execve")
#else
# error "Not define SEC_DEF_TRACEPOINT or SEC_DEF_TP"
#endif
int tracepoint__syscalls__sys_enter_execve(struct syscall_trace_enter *ctx)
{
	uid_t uid;
	pid_t pid;
	struct event_t *pevent = NULL;
	const char *filename = (void *)ctx->args[0];

	uid = (u32)bpf_get_current_uid_gid();
	pid = (pid_t)(bpf_get_current_pid_tgid() >> 32);

	if (bpf_map_update_elem(&execs, &pid, &zero_event, BPF_NOEXIST))
		return 0;

	pevent = bpf_map_lookup_elem(&execs, &pid);
	if (!pevent)
		return 0;

	pevent->pid = pid;
	pevent->uid = uid;

	bpf_core_read_user(&pevent->filename, sizeof(pevent->filename), filename);

	return 0;
}

/**
 * struct syscall_trace_exit {
 * 	struct trace_entry ent;
 * 	int nr;
 * 	long int ret;
 * };
 */

#if defined(SEC_DEF_TRACEPOINT)
SEC("tracepoint/syscalls/sys_exit_execve")
#elif defined(SEC_DEF_TP)
SEC("tp/syscalls/sys_exit_execve")
#endif
int tracepoint__syscalls__sys_exit_execve(struct syscall_trace_exit *ctx)
{
	pid_t pid;
	struct event_t *pevent = NULL;

	pid = (pid_t)(bpf_get_current_pid_tgid() >> 32);

	pevent = bpf_map_lookup_elem(&execs, &pid);
	if (!pevent)
		return 0;

	bpf_get_current_comm(&pevent->comm, sizeof(pevent->comm));

	pevent->ret = ctx->ret;

	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, pevent, sizeof(*pevent));

	bpf_map_delete_elem(&execs, &pid);
	return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
