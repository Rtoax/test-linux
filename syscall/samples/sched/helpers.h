#pragma once
#include <sched.h>

long int sys_getcpu(unsigned *cpu, unsigned *node);
void print_cpuset(cpu_set_t *cpuset);
