#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


int sys_pidfd_open(pid_t pid, int flags)
{
	int ret = syscall(__NR_pidfd_open, pid, flags, 0, 0, 0, 0);
	return ret >= 0 ? ret : -errno;
}

int main(void)
{
	int pidfd;
	pid_t pid;

	pid = fork();
	if (pid == 0) { /* If child */
		/* do something */
	} else if (pid > 0) { /* If parent */
		pidfd = sys_pidfd_open(pid, 0);
		printf("fd = %d\n", pidfd);
	}

	return 0;
}
