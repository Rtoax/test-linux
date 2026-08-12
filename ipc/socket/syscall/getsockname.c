#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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

	close(sockfd);
}

void free_port(void)
{
	struct sockaddr_in addr;
	int sock;
	socklen_t addr_len = sizeof(addr);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = 0; /* kernel alloc port */

	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

	getsockname(sock, (struct sockaddr *)&addr, &addr_len);

	printf("free port %d\n", ntohs(addr.sin_port));

	close(sock);
}

int main(void)
{
	test_socket(AF_INET, SOCK_STREAM, 0);
	test_socket(AF_INET, SOCK_DGRAM, 0);
	free_port();
	return 0;
}
