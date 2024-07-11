#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd;
	unsigned int seals;

	fd = open("/etc/os-release", O_RDONLY);
	if (fd == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	seals = fcntl(fd, F_GET_SEALS);
	if (seals == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	printf("Existing seals:");
	if (seals & F_SEAL_SEAL)
		printf(" SEAL");
	if (seals & F_SEAL_GROW)
		printf(" GROW");
	if (seals & F_SEAL_WRITE)
		printf(" WRITE");
#ifdef F_SEAL_FUTURE_WRITE
	if (seals & F_SEAL_FUTURE_WRITE)
		printf(" FUTURE_WRITE");
#endif
	if (seals & F_SEAL_SHRINK)
		printf(" SHRINK");
	printf("\n");

	/* Code to map the file and access the contents of the
	 * resulting mapping omitted */

	exit(EXIT_SUCCESS);
}
