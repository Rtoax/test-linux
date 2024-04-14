#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
	int fd;
	size_t size;
	ssize_t spliced;
	struct stat statbuf;

	fd = open("/etc/os-release", O_RDONLY);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	if (fstat(fd, &statbuf) < 0) {
		perror("fstat");
		return EXIT_FAILURE;
	}

	if (statbuf.st_size > INT_MAX) {
		fprintf(stderr, "Too big\n");
		return EXIT_FAILURE;
	}

	size = statbuf.st_size;

	/* splice(2) file to stdout. */
	spliced = splice(fd, NULL, STDOUT_FILENO, NULL, size, SPLICE_F_MOVE);
	if (spliced < 0) {
		fprintf(stderr, "splice: %m, try $ %s | cat\n", argv[0]);
		return EXIT_FAILURE;
	}

	close(fd);
	return EXIT_SUCCESS;
}
