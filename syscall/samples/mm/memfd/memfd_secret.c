/**
 * Since kernel 5.14 introduce memfd_secret(2)
 */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "helpers.h"

int main(void)
{
	int fd, ret = 0;

	fd = sys_memfd_secret(0);
	if (fd == -1) {
		fprintf(stderr, "memfd_secret: %m\n");
		ret = -errno;
	}

	close(fd);
	return ret;
}
