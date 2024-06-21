#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

int sys_gettid(void)
{
	int ret = syscall(__NR_gettid);
	return ret >= 0 ? ret : -errno;
}

int gettid(void)
{
	return sys_gettid();
}

int main(void)
{
	pid_t tid = gettid();

	printf("tid = %d, sys = %d\n", tid, sys_gettid());

	return 0;
}
