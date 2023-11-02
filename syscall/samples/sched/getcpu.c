#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sched.h>
#include <ctype.h>
#include <string.h>


long int sys_getcpu(unsigned *cpu, unsigned *node)
{
	return syscall(__NR_getcpu, cpu, node);
}

static void print_cpuset(cpu_set_t *cpuset)
{
	int j;
	for (j = 0; j < CPU_SETSIZE; j++)
		if (CPU_ISSET(j, cpuset))
			printf("CPU_SETSIZE = %d, j = %d\n", CPU_SETSIZE, j);
}

int main(void)
{
	int ret;
	unsigned int icpu, inode, bindcpu;
	cpu_set_t cpuset;
	long int ncpu = sysconf(_SC_NPROCESSORS_ONLN);


	/* Choice a cpu to bind */
	bindcpu = ncpu > 1 ? ncpu - 1 : 1;

	CPU_ZERO(&cpuset);
	CPU_SET(bindcpu, &cpuset);

	ret = sched_setaffinity(getpid(), sizeof(cpuset), &cpuset);
	if (ret) {
		perror("sched_setaffinity");
		return 1;
	}
	print_cpuset(&cpuset);

	icpu = inode = -1;
	ret = getcpu(&icpu, &inode);
	if (bindcpu != icpu) {
		fprintf(stderr, "sched_setaffinity(%d) != getcpu(%d).\n", bindcpu, icpu);
		assert(0);
	}

	printf("getcpu icpu = %d, inode = %d\n", icpu, inode);

	CPU_ZERO(&cpuset);
	ret = sched_getaffinity(getpid(), sizeof(cpuset), &cpuset);
	if (ret) {
		perror("sched_getaffinity");
		return 1;
	}
	print_cpuset(&cpuset);

	return 0;
}
