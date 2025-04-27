/**
 * Since kernel 5.14 introduce memfd_secret(2)
 *
 * create an anonymous RAM-based file to access secret memory regions.
 */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "memfd_helpers.h"

int main(void)
{
	int fd, ret = 0;

	fd = sys_memfd_secret(FD_CLOEXEC);
	if (fd == -1) {
		fprintf(stderr, "memfd_secret: %m\n");
		ret = -errno;
	}

	close(fd);
	return ret;
}
