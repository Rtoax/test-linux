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

#include "config.h"
#include "tcp_helpers.h"


int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr, cliaddr;
	int listenfd, connfd;
	pid_t childpid;
	char buf[MAX_LINE];
	socklen_t clilen;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		exit(1);
	}

	if (listen(listenfd, LISTENQ) < 0) {
		perror("listen error");
		exit(1);
	}

	for (;;) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if (connfd < 0) {
			perror("accept error");
			exit(1);
		}

		tcp_nodelay(connfd);

		printf("Accept new client: %s:%d\n",
			inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);

		if ((childpid = fork()) == 0) {
			close(listenfd);
			ssize_t n;
			char buf[MAX_LINE];
			while((n = read(connfd, buf, MAX_LINE)) > 0)
				write(connfd, buf, n);
			exit(0);
		}
		close(connfd);
	}

	close(listenfd);
}
