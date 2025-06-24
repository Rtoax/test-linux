/**
 * kernel commit [0] increase minimum default pipe size to 2 pages
 * [0] https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=46c4c9d1beb7f5b4cec4dd90e7728720583ee348
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>


int main(void)
{
	int pipefd[2];
	int pagesize = getpagesize();
	char *buf;
	size_t bufsz;

	if (pipe(pipefd) == -1) {
		perror("pipe");
		return 1;
	}

	bufsz = fcntl(pipefd[1], F_GETPIPE_SZ);
	printf("%zd, %ld pages\n", bufsz, (bufsz + 1) / pagesize);

	buf = calloc(bufsz, 1);
	write(pipefd[1], buf, bufsz);
	read(pipefd[0], buf, bufsz - 1);
	write(pipefd[1], buf, 1);

	free(buf);
	return 0;
}
