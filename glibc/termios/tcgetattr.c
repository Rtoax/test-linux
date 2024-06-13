#include <stdio.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>

#include "helpers.h"

int socket_fd(void)
{
	int sockfd, ret;
	struct termios t;

	sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
	ret = tcgetattr(sockfd, &t);
	if (ret) {
		fprintf(stderr, "ERROR: failed tcgetattr from socket fd.\n");
	} else {
		print_termios(&t);
	}

	close(sockfd);
	return ret;
}

int std_fd(void)
{
	struct termios t;

	tcgetattr(fileno(stdout), &t);

	print_termios(&t);

	return 0;
}

int main(void)
{
	std_fd();
	socket_fd();
	return 0;
}
