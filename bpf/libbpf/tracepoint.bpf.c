/**
 * BPF_PROG_TYPE_TRACEPOINT
 *
 * This programs are eBPF programs that attach to pre-defined trace points in
 * the linux kernel. These tracepoint are often placed in locations which are
 * interesting or common locations to measure performance.
 *
 * Refs:
 * - /sys/kernel/debug/tracing/events/
 * - /sys/kernel/tracing/available_events
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "tracepoint.h"
#include "bpf_misc.h"
#include "bpf_helpers.h"

#ifndef SIGKILL
#define SIGKILL 9
#endif

struct {
/**
 * BPF_MAP_TYPE_PERCPU_HASH
 *
 * This is the per-CPU variant of the BPF_MAP_TYPE_HASH map type.
 *
 * This map type is a generic map type with no restrictions on the structure
 * of the key and value. Hash-maps are implemented using a hash table, allowing
 * for lookups with arbitrary keys.
 *
 * This per-CPU version has a separate hash map for each logical CPU. When
 * accessing the map using most helper function, the hash map assigned to the
 * CPU the eBPF program is currently running on is accessed implicitly.
 */
#if defined(MAP_PERCPU_HASH)
	__uint(type, BPF_MAP_TYPE_PERCPU_HASH);
#elif defined(MAP_LRU_HASH)
	/**
	 * This map is the LRU (Least Recently Used) variant of the
	 * BPF_MAP_TYPE_HASH. It is a generic map type that stores a fixed
	 * maximum number of key/value pairs. When the map starts to get at
	 * capacity, the approximately least recently used elements is removed
	 * to make room for new elements.
	 */
	__uint(type, BPF_MAP_TYPE_LRU_HASH);
#elif defined(MAP_LRU_PERCPU_HASH)
	/**
	 *
	 */
	__uint(type, BPF_MAP_TYPE_LRU_PERCPU_HASH);
#elif defined(MAP_HASH)
	__uint(type, BPF_MAP_TYPE_HASH);
#else
# error "Must define MAP_PERCPU_HASH or MAP_HASH"
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

	bpf_core_read_user(&pevent->filename, sizeof(pevent->filename),
			   filename);

	return 0;
}

/**
 * struct syscall_trace_exit {
 * 	struct trace_entry ent;
 * 	int nr;
 * 	long int ret;
 * };
 */

/* see /sys/kernel/debug/tracing/events/syscalls/sys_enter_execve/ */
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

#if 1
	struct task_struct *task;
	task = bpf_task_from_pid(pid);
	if (task) {
		bpf_probe_read_kernel(pevent->comm2, sizeof(pevent->comm2),
				      task->comm);
		bpf_task_release(task);
	}
#endif

	/**
	 * TODO: Get cwd
	 */
	//bpf_getcwd(pevent->cwd, sizeof(pevent->cwd));
	bpf_get_current_comm(&pevent->comm, sizeof(pevent->comm));

	pevent->ret = ctx->ret;

#if defined(BPF_SEND_SIGNAL)
	if (str_eq(pevent->comm, "ls", 2)) {
		bpf_send_signal(SIGKILL);
		goto cleanup;
	}
#endif

	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, pevent,
			      sizeof(*pevent));

	goto cleanup; /* Skip compile warnings */
cleanup:
	bpf_map_delete_elem(&execs, &pid);
	return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
