#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sched.h>
#include <ctype.h>
#include <string.h>
/* FIXME: opencloudos 8.8 man shows getcpu() need this header */
//#include <linux/getcpu.h>

#include "sched_helpers.h"

#define getcpu(c, n) sys_getcpu(c, n)

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
		fprintf(stderr, "sched_setaffinity(%d) != getcpu(%d).\n",
			bindcpu, icpu);
		assert(0);
	}
	printf("getcpu icpu = %d, inode = %d\n", icpu, inode);

	icpu = -1;
	icpu = sched_getcpu();
	if (bindcpu != icpu) {
		fprintf(stderr, "sched_setaffinity(%d) != sched_getcpu(%d).\n",
			bindcpu, icpu);
		assert(0);
	}
	printf("sched_getcpu icpu = %d\n", icpu);

	CPU_ZERO(&cpuset);
	ret = sched_getaffinity(getpid(), sizeof(cpuset), &cpuset);
	if (ret) {
		perror("sched_getaffinity");
		return 1;
	}
	print_cpuset(&cpuset);

	return 0;
}
