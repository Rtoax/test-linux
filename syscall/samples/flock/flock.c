#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
	int fd;
	int ret;
	const char *filename = "testfile";

	if (argc > 1)
		filename = argv[1];

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	/* LOCK_RW = LOCK_READ | LOCK_WRITE */
	ret = flock(fd, LOCK_EX | LOCK_NB | LOCK_MAND | LOCK_READ | LOCK_WRITE);
	if (ret != 0) {
		fprintf(stderr, "flock: %s\n", strerror(errno));
		exit(1);
	}

	/* Hold flock for a little while */
	sleep(2);

	write(fd, "hello\n", sizeof("hello\n"));

	flock(fd, LOCK_UN);

	close(fd);
	return 0;
}
