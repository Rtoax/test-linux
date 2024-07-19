#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "common.h"

int tcpsocket_server(void)
{
	struct sockaddr_in6 servaddr;
	int listenfd;

	if ((listenfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_addr = in6addr_any;
	servaddr.sin6_port = htons(PORT);

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		return -1;
	}

	if (listen(listenfd, LISTENQ) < 0) {
		return -1;
	}

	return listenfd;
}

int tcpsocket_client(const char *ipv6)
{
	int sockfd;
	struct sockaddr_in6 servaddr;

	if (ipv6 == NULL) {
		return -1;
	}

	if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET;
	servaddr.sin6_port = htons(PORT);

	if (inet_pton(AF_INET6, ipv6, &servaddr.sin6_addr) < 0) {
		return -1;
	}

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		return -1;
	}
	return sockfd;
}

ssize_t readline(int fd, char *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;

	for (n = 1; n < maxlen; n++) {
		if ((rc = read(fd, &c, 1)) == 1) {
			*ptr++ = c;
			if (c == '\n') {
				break;
			}
		} else if (rc == 0) {
			*ptr = 0;
			return (n - 1);
		} else {
			return -1;
		}
	}
	*ptr = 0;
	return n;
}
