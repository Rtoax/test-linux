/**
 * Test:
 * while true; do for b in $(ls /dev/sd[a-z]); do sudo ./open $b; done; done
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	int fd;
	char *path = argv[1];
	if (!path) {
		fprintf(stderr, "ERROR: usage %s <file>.\n", argv[0]);
		exit(1);
	}

	if (access(path, F_OK) != 0) {
		fprintf(stderr, "ERROR: %s is not exist.\n", path);
		exit(1);
	}

	fd = open(path, O_NONBLOCK | O_RDWR);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	close(fd);
	return 0;
}
