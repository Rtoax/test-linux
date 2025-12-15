Tracepoint
==========

# Static Trace Point

- `/sys/kernel/tracing/available_events`
- `/sys/kernel/debug/tracing/events/`


# raw_tracepoint

- commit [bpf: introduce BPF_RAW_TRACEPOINT](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=c4f6699dfcb8558d138fe838f741b2c10f416cf9)


# Example

- include/trace/events/sched.h:`sched_process_fork`

```
/*
 * Tracepoint for kernel_clone:
 */
TRACE_EVENT(sched_process_fork,

	TP_PROTO(struct task_struct *parent, struct task_struct *child),

	TP_ARGS(parent, child),

	TP_STRUCT__entry(
		__string(	parent_comm,	parent->comm	)
		__field(	pid_t,		parent_pid	)
		__string(	child_comm,	child->comm	)
		__field(	pid_t,		child_pid	)
	),

	TP_fast_assign(
		__assign_str(parent_comm);
		__entry->parent_pid	= parent->pid;
		__assign_str(child_comm);
		__entry->child_pid	= child->pid;
	),

	TP_printk("comm=%s pid=%d child_comm=%s child_pid=%d",
		__get_str(parent_comm), __entry->parent_pid,
		__get_str(child_comm), __entry->child_pid)
);
```

- `/sys/kernel/debug/tracing/events/sched/sched_process_fork/format`

```
name: sched_process_fork
ID: 305
format:
	field:unsigned short common_type;	offset:0;	size:2;	signed:0;
	field:unsigned char common_flags;	offset:2;	size:1;	signed:0;
	field:unsigned char common_preempt_count;	offset:3;	size:1;	signed:0;
	field:int common_pid;	offset:4;	size:4;	signed:1;

	field:char parent_comm[16];	offset:8;	size:16;	signed:0;
	field:pid_t parent_pid;	offset:24;	size:4;	signed:1;
	field:char child_comm[16];	offset:28;	size:16;	signed:0;
	field:pid_t child_pid;	offset:44;	size:4;	signed:1;

print fmt: "comm=%s pid=%d child_comm=%s child_pid=%d", REC->parent_comm, REC->parent_pid, REC->child_comm, REC->child_pid
```

