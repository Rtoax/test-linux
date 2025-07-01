// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sched.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <linux/sched.h>

#include "sched_helpers.h"


void print_cpuset(cpu_set_t *cpuset)
{
	int j;
	bool has = false;
	for (j = 0; j < CPU_SETSIZE; j++) {
		if (CPU_ISSET(j, cpuset)) {
			has = true;
			printf("%d,", j);
		}
	}
	if (has)
		printf("\n");
}

static const char *next_token(const char *q, int sep)
{
	if (q)
		q = strchr(q, sep);
	if (q)
		q++;

	return q;
}

static int next_num(const char *str, char **end, int *result)
{
	if (!str || *str == '\0' || !isdigit(*str))
		return -1;

	*result = strtoul(str, end, 10);
	if (str == *end)
		return -1;

	return 0;
}

/* set current thread cpu affinity to cpu list, this function works like
 * taskset command (actually cpulist parsing logic reference to util-linux).
 * example of this function: "0,2,3", "0,2-3", "0-20:2". */
int str2cpuset(const char *cpulist, cpu_set_t *cpuset)
{
	const char *p, *q;
	char *end = NULL;
	cpu_set_t tmpcpuset;

	if (!cpulist)
		return -EINVAL;

	CPU_ZERO(&tmpcpuset);

	q = cpulist;
	while (p = q, q = next_token(q, ','), p) {
		int a, b, s;
		const char *c1, *c2;

		if (next_num(p, &end, &a) != 0)
			return -EINVAL;

		b = a;
		s = 1;
		p = end;

		c1 = next_token(p, '-');
		c2 = next_token(p, ',');

		if (c1 != NULL && (c2 == NULL || c1 < c2)) {
			if (next_num(c1, &end, &b) != 0)
				return -EINVAL;

			c1 = end && *end ? next_token(end, ':') : NULL;
			if (c1 != NULL && (c2 == NULL || c1 < c2)) {
				if (next_num(c1, &end, &s) != 0)
					return -EINVAL;

				if (s == 0)
					return -EINVAL;
			}
		}

		if ((a > b))
			return -EINVAL;

		while (a <= b) {
			CPU_SET(a, &tmpcpuset);
			a += s;
		}
	}

	if (end && *end)
		return -EINVAL;

	memcpy(cpuset, &tmpcpuset, sizeof(cpu_set_t));
	return 0;
}

/**
 * @cpu_list: The cpu list should like 1-3,6
 */
int taskset(int pid, char *cpu_list)
{
	cpu_set_t cpu_set;
	CPU_ZERO(&cpu_set);
	str2cpuset(cpu_list, &cpu_set);
	sched_setaffinity(pid, sizeof(cpu_set_t), &cpu_set);
	return 0;
}

const char *sched_policy_string(int policy)
{
	switch (policy) {
#define CASE(P)	case P: return #P; break
# include "sched_policy.h"
	default:
		return "Unknown";
#undef CASE
	}
}

long int sys_getcpu(unsigned *cpu, unsigned *node)
{
	return syscall(__NR_getcpu, cpu, node);
}

int sys_sched_setattr(pid_t pid, const struct __sched_attr *attr,
		      unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sys_sched_getattr(pid_t pid, struct __sched_attr *attr, unsigned int size,
		      unsigned int flags)
{
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
}
