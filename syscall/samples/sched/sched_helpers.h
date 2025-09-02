// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdint.h>
#include <unistd.h>
#include <sched.h>
#include <syscall.h>
#include <sys/syscall.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

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

/* Could use linux/sched/types.h instead */
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

#define gettid() sys_gettid()
int sys_gettid(void);
long int sys_getcpu(unsigned *cpu, unsigned *node);

void print_cpuset(cpu_set_t * cpuset);
int str2cpuset(const char *cpulist, cpu_set_t *cpuset);
int taskset(int pid, char *cpu_list);
const char *sched_policy_string(int policy);

int sys_sched_getattr(pid_t pid, struct __sched_attr *attr, unsigned int size,
		      unsigned int flags);
int sys_sched_setattr(pid_t pid, const struct __sched_attr *attr, unsigned int flags);

