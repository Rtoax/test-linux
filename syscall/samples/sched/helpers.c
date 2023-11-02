#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sched.h>
#include <ctype.h>
#include <string.h>

#include "helpers.h"


long int sys_getcpu(unsigned *cpu, unsigned *node)
{
	return syscall(__NR_getcpu, cpu, node);
}

void print_cpuset(cpu_set_t *cpuset)
{
	int j;
	for (j = 0; j < CPU_SETSIZE; j++)
		if (CPU_ISSET(j, cpuset))
			printf("CPU_SETSIZE = %d, j = %d\n", CPU_SETSIZE, j);
}
