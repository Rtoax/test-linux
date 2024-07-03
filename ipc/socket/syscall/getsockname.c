#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>

int sockfd_to_family(int sockfd)
{
	struct sockaddr_storage ss;
	socklen_t len;

	len = sizeof(ss);

	if (getsockname(sockfd, (struct sockaddr *)&ss, &len) < 0) {
		return -1;
	}
	return ss.ss_family;
}

int main(void)
{
	int sockfd, family;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	family = sockfd_to_family(sockfd);

	assert(AF_INET == family && "call getsockname failed");

	printf("AF_INET = %d\n", AF_INET);
	printf("family  = %d\n", family);

	return 0;
}
