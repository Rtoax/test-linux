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
	printf("SO_SNDBUF: optval = %d, optlen = %d\n", val, len);

	getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &val, &len);
	printf("SO_RCVBUF: optval = %d, optlen = %d\n", val, len);

	getsockopt(sockfd, SOL_SOCKET, SO_TYPE, &val, &len);
	printf("SO_TYPE: optval = %d, optlen = %d\n", val, len);

	close(sockfd);
}

int main(void)
{
	test(AF_INET, SOCK_STREAM);
	test(AF_INET, SOCK_DGRAM);
	return 0;
}

