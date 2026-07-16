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
#include <linux/version.h>
#include "tracepoint.h"
#include "bpf_misc.h"
#include "bpf_helpers.bpf.h"
#include "string_helpers.bpf.h"
#include "cgroup.bpf.h"
#include "task.bpf.h"
#include "stack_helpers.bpf.h"


#ifndef SIGKILL
#define SIGKILL 9
#endif

#if defined(SEC_DEF_TRACEPOINT)
# define SEC_TRACEPOINT	"tracepoint"
#elif defined(SEC_DEF_TP)
# define SEC_TRACEPOINT	"tp"
#else
# error "Not define SEC_DEF_TRACEPOINT or SEC_DEF_TP"
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

SEC(SEC_TRACEPOINT "/syscalls/sys_enter_execve")
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

	__get_stack(ctx);

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
SEC(SEC_TRACEPOINT "/syscalls/sys_exit_execve")
int tracepoint__syscalls__sys_exit_execve(struct syscall_trace_exit *ctx)
{
	pid_t pid;
	struct event_t *pevent = NULL;

	pid = (pid_t)(bpf_get_current_pid_tgid() >> 32);

	pevent = bpf_map_lookup_elem(&execs, &pid);
	if (!pevent)
		return 0;

#ifdef PARSE_AUXV
	struct task_struct *task = (struct task_struct *)bpf_get_current_task();
	struct mm_struct *mm = BPF_CORE_READ(task, mm);
	if (mm) {
		unsigned long *saved_auxv = BPF_CORE_READ(mm, saved_auxv);
		struct auxv_entry entry;
		bpf_probe_read_kernel(&entry, sizeof(entry), (void *)(saved_auxv + 6));
		pevent->auxv.type = entry.type;
		pevent->auxv.val = entry.val;
		/* FIXME: how to parse all auxv */
	}
#endif

/* bpf_cgroup_from_id() since v6.12 support tracepoint */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
	pevent->cgrp_level = cgroup_level();
#endif
	task_comm_from_pid(pid, pevent->comm2, sizeof(pevent->comm2));

#if defined(SUPPORT_BPF_TASK_CWD_FROM_PID)
# ifdef DEBUG
#  pragma message "support bpf_task_cwd_from_pid()"
# endif
	extern int bpf_task_cwd_from_pid(s32 pid, char *buf, u32 buf_len) __weak __ksym;
	/**
	 * https://github.com/Rtoax/linux/tree/p056-bpf_task_cwd
	 */
	bpf_task_cwd_from_pid(pid, pevent->cwd, sizeof(pevent->cwd));
#else
	bpf_getcwd(pevent->cwd, sizeof(pevent->cwd));
#endif

	bpf_get_current_comm(&pevent->comm, sizeof(pevent->comm));

	pevent->ret = ctx->ret;

#if defined(SUPPORT_BPF_SEND_SIGNAL)
	bool should_kill = false;
# if defined(SUPPORT_BPF_STRCMP)
	should_kill |= !bpf_strcmp(pevent->comm, "free");
# endif
# if defined(SUPPORT_BPF_STRCASECMP)
	should_kill |= !bpf_strcasecmp(pevent->comm, "FIND");
# endif
	should_kill |= !strncmp(pevent->comm, "top", 3);
# if defined(SUPPORT_BPF_STRNSTR)
	should_kill |= bpf_strnstr(pevent->comm, "ls", 2) >= 0;
# endif
# if defined(SUPPORT_BPF_STRCASESTR)
	should_kill |= bpf_strcasestr(pevent->comm, "xxx") >= 0;
	should_kill |= bpf_strcasestr(pevent->comm, "YYY") >= 0;
# endif
# if defined(SUPPORT_BPF_STRNLEN)
	/* $ ./aaaaaaaaaa */
	should_kill |= bpf_strnlen(pevent->comm, 100) >= 10;
# endif
# if defined(SUPPORT_BPF_STRSTR)
	should_kill |= bpf_strstr(pevent->comm, "openat") >= 0;
# endif
	if (should_kill) {
		bpf_send_signal(SIGKILL);
		goto cleanup;
	}
#endif

	/**
	 * test string_helpers.bpf.h
	 */
	{
#ifdef SUPPORT_BPF_STRCAT
		int err = 0;
		bpf_printk("origin comm %s", pevent->comm);
		err = bpf_strcat(pevent->comm, sizeof(pevent->comm), "XYZ");
		if (err < 0)
			bpf_printk("bpf_strcat(%s) failed, %d", pevent->comm,
				   err);
		bpf_printk("bpf_strcat(%s), err %d", pevent->comm, err);
#ifdef SUPPORT_BPF_STRNCAT
		err = bpf_strncat(pevent->comm, sizeof(pevent->comm), "ABC", 2);
		if (err < 0)
			bpf_printk("bpf_strncat(%s) failed, %d", pevent->comm,
				   err);
		bpf_printk("bpf_strncat(%s), err %d", pevent->comm, err);
#endif
#endif

		__bpf_str_prepend(pevent->comm, sizeof(pevent->comm), "/", 2);
		/* beyond the boundary of comm[], skip */
		__bpf_str_prepend(pevent->comm, sizeof(pevent->comm),
				  "12345678901234567890", 21);
		__bpf_str_append(pevent->comm, sizeof(pevent->comm), ".elf");
		/* beyond the boundary of comm[], truncate */
		__bpf_str_append(pevent->comm, sizeof(pevent->comm),
				 ".1.2.3.4.5.6.7.8.9.0");

		/**
		 * TODO: BPF program is too large. Processed 1000001 insn
		 */
		// __bpf_str_prepend(pevent->cwd, sizeof(pevent->cwd), "/", 2);
	}

	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, pevent,
			      sizeof(*pevent));

	goto cleanup; /* Skip compile warnings */
cleanup:
	bpf_map_delete_elem(&execs, &pid);
	return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
