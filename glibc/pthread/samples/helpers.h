#pragma once

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setattr     314
#define __NR_sched_getattr     315
#endif

#ifdef __i386__
#define __NR_sched_setattr     351
#define __NR_sched_getattr     352
#endif

#ifdef __arm__
#define __NR_sched_setattr     380
#define __NR_sched_getattr     381
#endif

struct __sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};


/**
 * @cpu_list: The cpu list should like 1-3,6
 */
int taskset(int pid, char *cpu_list);

int sys_sched_setattr(pid_t pid, const struct __sched_attr *attr, unsigned int flags);
int sys_sched_getattr(pid_t pid, struct __sched_attr *attr, unsigned int size,
		      unsigned int flags);
