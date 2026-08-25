#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syscall.h>
#include <linux/close_range.h>

int sys_close_range(unsigned int fd, unsigned int max_fd, unsigned int flags)
{
	return syscall(__NR_close_range, fd, max_fd, flags);
}

/**
 * since linux 5.9, glibc 2.34 support close_range() wrapper
 */
#if defined(__GLIBC__) && __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 34
#else
# define close_range sys_close_range
#endif

int main(void)
{
	int ret;
	int pipefd[2];

	pipe(pipefd);

	ret = close_range(pipefd[0], pipefd[1], CLOSE_RANGE_CLOEXEC);
	if (ret) {
		fprintf(stderr, "close_range: %m\n");
		exit(1);
	}

	ret = close_range(0, 3, CLOSE_RANGE_CLOEXEC);
	if (ret) {
		fprintf(stderr, "close_range: %m\n");
		exit(1);
	}
	/* FIXME: Still print fine */
	fprintf(stdout, "hello.\n");

	return 0;
}
