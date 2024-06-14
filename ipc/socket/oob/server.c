/**
 * 使用SIGURG检测带外数据是否到达
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define BUF_SIZE 1024
#define port 8888

static int connfd;

void sig_urg(int sig)
{
	int save_errno = errno;
	char buffer[BUF_SIZE];
	int ret;

	printf("SIGURG signal.\n");

	memset(buffer, '\0', BUF_SIZE);
	ret = recv(connfd, buffer, BUF_SIZE-1, MSG_OOB);
	printf("got %d bytes of oob data '%s'\n", ret, buffer);

	errno = save_errno;
}

void addsig(int sig, void (*sig_handler)(int))
{
	struct sigaction sa;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = sig_handler;
	sa.sa_flags |= SA_RESTART;
	sigfillset(&sa.sa_mask);
	assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char* argv[])
{
	int ret, sock;
	struct sockaddr_in address;
	struct sockaddr_in client;
	socklen_t client_addrlength = sizeof(client);

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0 && "socket failed.");

	ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1 && "bind failed.");

	ret = listen(sock, 5);
	assert(ret != -1 && "listen failed.");

	connfd = accept(sock, (struct sockaddr* )&client, &client_addrlength);
	if (connfd < 0) {
		printf( "errno is: %d\n", errno );
		exit(1);
	}

	addsig(SIGURG, sig_urg);

	/* 使用 SIGURG 信号之前，必须设置socket的宿主进程或进程组 */
	fcntl(connfd, F_SETOWN, getpid());

	char buffer[BUF_SIZE];
	while (1) {
		memset(buffer, '\0', BUF_SIZE);
		ret = recv(connfd, buffer, BUF_SIZE - 1, 0);
		if (ret <= 0) {
			break;
		}
		printf("got %d bytes of normal data '%s'\n", ret, buffer);
	}
	close(connfd);

	close(sock);
	return 0;
}
