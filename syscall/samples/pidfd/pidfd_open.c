#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include <linux/version.h>

/* pidfd_open: kernel >= 5.2.0 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 2, 0)
#define __NR_pidfd_open -1
#endif

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
	if (pid == 0) {		/* If child */
		/* do something */
	} else if (pid > 0) {	/* If parent */
		pidfd = sys_pidfd_open(pid, 0);
		printf("fd = %d\n", pidfd);
	}

	return 0;
}
