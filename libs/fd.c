#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int setnonblock(int fd)
{
	int opts;
	opts = fcntl(fd, F_GETFL);
	if (opts < 0) {
		perror("fcntl(sock, GETFL) error");
		return -errno;
	}
	opts = opts|O_NONBLOCK;
	if (fcntl(fd, F_SETFL, opts) < 0) {
		perror("fcntl(sock, SETFL, opts)");
		return -errno;
	}
	return 0;
}

