/**
 * kernel commit [0] increase minimum default pipe size to 2 pages
 * [0] https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=46c4c9d1beb7f5b4cec4dd90e7728720583ee348
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>


int main(void)
{
	int pipefd[2];
	for (int i = 0; i < 1025; i++)
		if (pipe(pipefd) == -1)
			return 1;
	size_t bufsz = fcntl(pipefd[1], F_GETPIPE_SZ);
	printf("%zd\n", bufsz);
	char *buf = calloc(bufsz, 1);
	write(pipefd[1], buf, bufsz);
	read(pipefd[0], buf, bufsz-1);
	write(pipefd[1], buf, 1);

	return 0;
}
