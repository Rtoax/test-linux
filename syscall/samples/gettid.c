/**
 * pid_t gettid(void);
 *
 * There is no glibc wrapper for this system call on glibc 2.28.
 */
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

#if !__GLIBC_PREREQ(2, 29)
int gettid(void)
{
	return sys_gettid();
}
#endif

int main(void)
{
	pid_t tid = gettid();

	printf("tid = %d, sys = %d\n", tid, sys_gettid());

	return 0;
}
