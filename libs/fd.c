#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

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

