#pragma once
#include <sched.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

long int sys_getcpu(unsigned *cpu, unsigned *node);
void print_cpuset(cpu_set_t *cpuset);
int str2cpuset(const char *cpulist, cpu_set_t *cpuset);
