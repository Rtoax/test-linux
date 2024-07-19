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

int main(int argc, char *argv[])
{
	struct sockaddr_in cliaddr;
	int listenfd, connfd;
	pid_t childpid;
	char buf[MAX_LINE];
	socklen_t clilen;

	if ((listenfd = tcpsocket_server())<0) {
		perror("socket error");
		exit(1);
	}

	clilen = sizeof(cliaddr);

	for (;;) {
		if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
			perror("accept error");
			exit(1);
		}

		if ((childpid = fork()) == 0) {
			close(listenfd);
			ssize_t n;
			memset(buf, 0, MAX_LINE);
			while ((n = read(connfd, buf, MAX_LINE)) > 0) {
				printf("Server: %s\n", buf);
				buf[0] = 'A';
				write(connfd, buf, MAX_LINE);
			}
			exit(0);
		}
		close(connfd);
	}
	close(listenfd);

}
