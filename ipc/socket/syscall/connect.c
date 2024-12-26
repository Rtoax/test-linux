#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "fd.h"

void set_sock_timeout(int sockfd, int secs)
{
	int ret;
	struct timeval timeout;
	socklen_t len = sizeof(timeout);

	timeout.tv_sec = secs;
	timeout.tv_usec = 0;

	ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
	assert(ret != -1);
}

//https://www.cnblogs.com/Anker/p/6413642.html
int main(int argc, char **argv)
{
	char *ipaddr = "10.12.1.214"; /* non exist */
	unsigned int port = 80;
	int fd = 0;
	struct sockaddr_in addr;
	fd_set fdr, fdw;
	struct timeval timeout;
	int err = 0;
	int errlen = sizeof(err);

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		fprintf(stderr, "create socket failed,error: %m.\n");
		return -1;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ipaddr, &addr.sin_addr);

	set_sock_timeout(fd, 10);
	setnonblock(fd);

	/* 阻塞情况下linux系统默认超时时间为75s */
	int rc = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
	if (rc != 0) {
		/* see manual connect(2) */
		if (errno == EINPROGRESS) {
			printf("Doing connection.\n");
			FD_ZERO(&fdr);
			FD_ZERO(&fdw);
			FD_SET(fd, &fdr);
			FD_SET(fd, &fdw);
			timeout.tv_sec = 10;
			timeout.tv_usec = 0;
			rc = select(fd + 1, &fdr, &fdw, NULL, &timeout);
			if (rc < 0) {
				fprintf(stderr, "select error: %m\n");
				close(fd);
				return -1;
			}
			if (rc == 0) {
				fprintf(stderr, "Connect timeout.\n");
				close(fd);
				return -1;
			}
			/* [1] 当连接成功建立时，描述符变成可写, rc = 1 */
			if (rc == 1 && FD_ISSET(fd, &fdw)) {
				printf("Connect success\n");
				close(fd);
				return 0;
			}
			/**
			 * [2] 当连接建立遇到错误时，描述符变为即可读，也可写，
			 * rc = 2 遇到这种情况，可调用getsockopt函数
			 */
			if (rc == 2) {
				if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err,
						(socklen_t *)&errlen) == -1) {
					fprintf(stderr, "getsockopt(SO_ERROR): %m");
					close(fd);
					return -1;
				}

				if (err) {
					errno = err;
					fprintf(stderr, "connect error: %m\n");
					close(fd);
					return -1;
				}
			}
		}
		fprintf(stderr, "connect failed, error: %m.\n");
		return -1;
	}
	return 0;
}

