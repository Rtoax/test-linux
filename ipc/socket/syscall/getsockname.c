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

void test_socket(int af, int type, int proto)
{
	int sockfd, family;

	sockfd = socket(af, type, proto);
	family = sockfd_to_family(sockfd);

	assert(af == family && "call getsockname failed");

	printf("family = %d\n", family);
}

int main(void)
{
	test_socket(AF_INET, SOCK_STREAM, 0);
	test_socket(AF_INET, SOCK_DGRAM, 0);
	return 0;
}
