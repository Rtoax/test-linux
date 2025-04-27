#include <stdio.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>

#include "termios_helpers.h"

int socket_fd(void)
{
	int sockfd, ret;
	struct termios t;

	sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
	ret = tcgetattr(sockfd, &t);
	if (ret) {
		fprintf(stderr, "ERROR: failed tcgetattr from socket fd %d.\n", sockfd);
	} else {
		print_termios(&t);
	}

	close(sockfd);
	return ret;
}

int std_fd(int fd)
{
	int ret;
	struct termios t;

	ret = tcgetattr(fd, &t);
	if (ret) {
		fprintf(stderr, "ERROR: failed tcgetattr from fd %d.\n", fd);
	} else {
		print_termios(&t);
	}

	return 0;
}

int main(void)
{
	std_fd(fileno(stdin));
	std_fd(fileno(stdout));
	std_fd(fileno(stderr));
	socket_fd();
	return 0;
}
