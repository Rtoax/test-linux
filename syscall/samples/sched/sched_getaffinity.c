#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "libs/memshow.h"

int main(void)
{
	int ret;
	unsigned int bindcpu;
	cpu_set_t cpuset;
	pid_t pid;
	long int ncpu = sysconf(_SC_NPROCESSORS_ONLN);

	pid = getpid();
	bindcpu = ncpu > 1 ? ncpu - 1 : 1;

	ret = sched_getaffinity(pid, sizeof(cpu_set_t), &cpuset);
	if (ret) {
		perror("sched_getaffinity");
		return ret;
	}
	fhexdump(stdout, "cpuset > ", &cpuset, sizeof(cpu_set_t));

	CPU_ZERO(&cpuset);
	CPU_SET(bindcpu, &cpuset);
	ret = sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset);
	if (ret) {
		perror("sched_setaffinity");
		return ret;
	}
	fhexdump(stdout, "cpuset > ", &cpuset, sizeof(cpu_set_t));

	return 0;
}
