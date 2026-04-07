// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int setnonblock(int fd)
{
	int flags;
	flags = fcntl(fd, F_GETFL);
	if (flags < 0) {
		perror("fcntl(sock, GETFL) error");
		return -errno;
	}
	flags = flags | O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0) {
		perror("fcntl(sock, SETFL, flags)");
		return -errno;
	}
	return 0;
}

#ifdef TEST_MAIN
int main(void)
{
	setnonblock(0);
	return 0;
}
#endif
