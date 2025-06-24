/**
 * Zero copy TCP echo server
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <poll.h>
#include <fcntl.h>


#define MYPORT	8888
#define BACKLOG	10
#define MAXDATASIZE	1024
#define FILEMAX	3000

int main(void)
{
	int i, maxi;
	int listenfd, connfd, sockfd;
	int nready;
	struct pollfd client[FILEMAX];
	struct sockaddr_in seraddr;
	struct sockaddr_in cliaddr;
	socklen_t sin_size;
	int on = 1;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(MYPORT);
	seraddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(seraddr.sin_zero), 8);

	if ((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
		perror("socket");
		exit(1);
	}

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
		perror("setsockopt");
		exit(1);
	}

	if (bind(listenfd, (struct sockaddr *)&seraddr, sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(listenfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	printf("listen on port %d localhost\n", MYPORT);
	printf("connect with command\n$ nc 0 %d\n", MYPORT);

	client[0].fd = listenfd;
	client[0].events = POLLIN;

	for (i = 1; i < FILEMAX; i++){
		client[i].fd = -1;
	}

	maxi = 0;
	while (1) {
		nready = poll(client, maxi + 1, -1);
		if (nready < 0) {
			perror("poll error!\n");
			exit(1);
		}

		if (client[0].revents & POLLIN) {
			sin_size = sizeof(cliaddr);
			if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &sin_size))==-1) {
				perror("accept");
				exit(1);
			}
			printf("client IP: %s\t PORT : %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
			for (i = 1; i < FILEMAX; i++) {
				if (client[i].fd < 0) {
					client[i].fd = connfd;
					break;
				}
			}
			if (i == FILEMAX) {
				perror("too many clients!\n");
				exit(1);
			}

			client[i].events = POLLIN;
			if (i > maxi)
				maxi = i;

			if (--nready == 0)
				continue;
		}

		for (i = 1; i <= maxi; i++) {
			if ((sockfd = client[i].fd) < 0)
				continue;
			if (client[i].revents & POLLIN) {
				int ret;
				int flags = SPLICE_F_MORE | SPLICE_F_MOVE;
				int pipefd[2];
				ret = pipe(pipefd);
				if (ret == -1) {
					perror("pipe error");
					exit(1);
				}

				/* FIXME: why 0 is faster */
				flags = 0;

				ret = splice(sockfd, NULL, pipefd[1], NULL, 1024, flags);
				if (ret == -1) {
					perror("splice error");
					exit(1);
				}
				ret = splice(pipefd[0], NULL, sockfd, NULL, 1024, flags);
				if (ret == -1) {
					perror("splice error");
					exit(1);
				}
			}
		}
	}
	return 0;
}
