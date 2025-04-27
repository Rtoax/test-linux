#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>

#include <stdbool.h>
#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <syscall.h>

#include "pthread_helpers.h"

/* Both Process and CPU ids should be positive numbers. */
static int convert_str_to_int(char* begin)
{
	if (!begin) {
		errx(1, "Invalid arguments for %s", __func__);
	}

	errno = 0;
	char *end = NULL;
	long num = strtol(begin, &end, 10);
	if (errno || (*end != '\0') || (num > INT_MAX) || (num < 0)) {
		errx(1, "Invalid integer: %s", begin);
	}
	return (int)num;
}

/*
 * The cpu list should like 1-3,6
 */
static void parse_cpu_list(char* cpu_list, cpu_set_t* cpu_set)
{
	if (!cpu_list || !cpu_set) {
		errx(1, "Invalid arguments for %s", __func__);
	}
	int i;
	char* begin = cpu_list;
	while (1) {
		bool last_token = false;
		char* end = strchr(begin, ',');
		if (!end) {
			last_token = true;
		} else {
			*end = '\0';
		}

		char* hyphen = strchr(begin, '-');
		if (hyphen) {
			*hyphen = '\0';
			int first_cpu = convert_str_to_int(begin);
			int last_cpu = convert_str_to_int(hyphen + 1);
			if ((first_cpu > last_cpu) || (last_cpu >= CPU_SETSIZE)) {
				errx(1, "Invalid cpu list: %s", cpu_list);
			}
			for (i = first_cpu; i <= last_cpu; i++) {
				CPU_SET(i, cpu_set);
			}
		} else {
			CPU_SET(convert_str_to_int(begin), cpu_set);
		}

		if (last_token) {
			break;
		} else {
			begin = end + 1;
		}
	}
}

/**
 * @cpu_list: The cpu list should like 1-3,6
 */
int taskset(int pid, char *cpu_list)
{
	cpu_set_t cpu_set;
	CPU_ZERO(&cpu_set);
	parse_cpu_list(cpu_list, &cpu_set);
	sched_setaffinity(pid, sizeof(cpu_set_t), &cpu_set);
	return 0;
}

int sys_sched_setattr(pid_t pid, const struct __sched_attr *attr, unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sys_sched_getattr(pid_t pid, struct __sched_attr *attr, unsigned int size,
		      unsigned int flags)
{
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
}

