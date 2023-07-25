#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>


int main(void)
{
	int fd;
	int ret;

	fd = open("testfile", O_CREAT | O_TRUNC | O_RDWR, 0644);

	ret = flock(fd, LOCK_EX | LOCK_NB);
	if (ret != 0) {
		fprintf(stderr, "flock: %s\n", strerror(errno));
		exit(1);
	}

	write(fd, "hello\n", sizeof("hello\n"));

	flock(fd, LOCK_UN);

	close(fd);
	return 0;
}
