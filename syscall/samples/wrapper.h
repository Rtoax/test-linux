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

