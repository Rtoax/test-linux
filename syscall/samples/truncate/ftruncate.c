/**
 * More to see truncate(2)
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "syscall_helpers.h"

int main(int argc, char *argv[])
{
	int fd, ret, len;
	const char *file = "tmp.dat";

	len = 1024;

	create_file(file, 'a', len);

	fd = open(file, O_RDWR);

	ret = ftruncate(fd, len / 2);
	if (ret == -1) {
		fprintf(stderr, "truncate %m\n");
		return -errno;
	}

	close(fd);

	return 0;
}

