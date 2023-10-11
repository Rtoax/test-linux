#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>


int main()
{
	int sockfd;
	int val;
	socklen_t len = sizeof(socklen_t);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &val, &len);
	printf("SO_SNDBUF: optval = %d, optlen = %d\n", val, len);

	getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &val, &len);
	printf("SO_RCVBUF: optval = %d, optlen = %d\n", val, len);

	getsockopt(sockfd, SOL_SOCKET, SO_TYPE, &val, &len);
	printf("SO_TYPE: optval = %d, optlen = %d\n", val, len);

	close(sockfd);
}
