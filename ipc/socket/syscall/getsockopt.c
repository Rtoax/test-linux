#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>


void test(int domain, int type)
{
	int sockfd;
	int val;
	socklen_t len = sizeof(socklen_t);

	sockfd = socket(domain, type, 0);

	getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &val, &len);
	printf("%-20s: optval = %-8d, optlen = %-8d\n", "SO_SNDBUF", val, len);

	getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &val, &len);
	printf("%-20s: optval = %-8d, optlen = %-8d\n", "SO_RCVBUF", val, len);

	getsockopt(sockfd, SOL_SOCKET, SO_TYPE, &val, &len);
	printf("%-20s: optval = %-8d, optlen = %-8d\n", "SO_TYPE", val, len);

	close(sockfd);
}

int main(void)
{
	test(AF_INET, SOCK_STREAM);
	test(AF_INET, SOCK_DGRAM);
	test(AF_INET6, SOCK_STREAM);
	test(AF_INET6, SOCK_DGRAM);
	test(AF_UNIX, SOCK_STREAM);
	test(AF_UNIX, SOCK_DGRAM);
	return 0;
}

