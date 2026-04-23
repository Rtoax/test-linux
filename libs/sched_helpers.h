// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <unistd.h>
#include <sched.h>
#include <linux/sched.h>
#ifdef __has_include
# if __has_include("linux/sched/types.h")
#  define sched_param __mask_sched_param
#   include <linux/sched/types.h>
#  undef sched_param
# endif
#endif

void print_cpuset(cpu_set_t * cpuset);
int str2cpuset(const char *cpulist, cpu_set_t *cpuset);
int taskset(int pid, char *cpu_list);
const char *sched_policy_string(int policy);

/* Syscalls */
#define gettid() sys_gettid()
int sys_gettid(void);

long int sys_getcpu(unsigned *cpu, unsigned *node);

int sys_sched_getattr(pid_t pid, struct sched_attr *attr, unsigned int size,
		      unsigned int flags);
int sys_sched_setattr(pid_t pid, const struct sched_attr *attr,
		      unsigned int flags);

#if !defined(__aarch64__)
int sys_fork(void);
int sys_vfork(void);
#endif
