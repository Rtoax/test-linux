#define __USE_GNU
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <libs/memshow.h>

int main(void)
{
	int ret;
	cpu_set_t cpuset;
	pid_t pid;

	CPU_ZERO(&cpuset);

	pid = getpid();

	ret = sched_getaffinity(pid, sizeof(cpu_set_t), &cpuset);

	printf("ret = %d\n", ret);

	memshow("cpuset > ", &cpuset, sizeof(cpu_set_t));

	return 0;
}
