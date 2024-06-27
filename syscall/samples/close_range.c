#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syscall.h>
#include <linux/close_range.h>

int sys_close_range(unsigned int fd, unsigned int max_fd, unsigned int flags)
{
	return syscall(__NR_close_range, fd, max_fd, flags);
}

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

	return 0;
}
