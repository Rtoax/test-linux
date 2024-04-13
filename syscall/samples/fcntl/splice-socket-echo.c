#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <fcntl.h>


int main(int argc, char **argv)
{
	int connfd, ret, reuse = 1, sock, pipefd[2];
	char *ip;
	int port;
	struct sockaddr_in address;

	ip = "127.0.0.1";
	port = 1234;

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip, &address.sin_addr);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

	ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, 5);
	assert(ret != -1);

	struct sockaddr_in client;
	socklen_t client_addrlength = sizeof(client);

	printf("listen on %s:%d\n", ip, port);
	printf("connect with command\n$ nc %s %d\n", ip, port);

	connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
	if (connfd < 0) {
		fprintf(stderr, "accept: %s\n", strerror(errno));
		exit(1);
	}

	/* [0]: read, [1]: write */
	ret = pipe(pipefd);
	assert(ret != -1);

	while (1) {
		int flags = SPLICE_F_MORE | SPLICE_F_MOVE;

		/* 将 connfd 上流入的客户端数据定向到管道中 */
		ret = splice(connfd, NULL, pipefd[1], NULL, 1024, flags);
		assert(ret != -1);

		/* 将管道的输出定向到 connfd 连接文件符上 */
		ret = splice(pipefd[0], NULL, connfd, NULL, 1024, flags);
		assert(ret != -1);
	}
	close(connfd);
	close(sock);
	return 0;
}
