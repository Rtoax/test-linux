#pragma once

#include <stdint.h>

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
	uint32_t size;

	uint32_t sched_policy;
	uint64_t sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	int32_t sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	uint32_t sched_priority;

	/* SCHED_DEADLINE (nsec) */
	uint64_t sched_runtime;
	uint64_t sched_deadline;
	uint64_t sched_period;
};


/**
 * @cpu_list: The cpu list should like 1-3,6
 */
int taskset(int pid, char *cpu_list);

int sys_sched_setattr(pid_t pid, const struct __sched_attr *attr, unsigned int flags);
int sys_sched_getattr(pid_t pid, struct __sched_attr *attr, unsigned int size,
		      unsigned int flags);
