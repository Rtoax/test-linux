#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <poll.h>
#include <limits.h> /* for OPEN_MAX */
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#ifndef _Included_swap
#define _Included_swap
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CLIENTS	1024
#define LISTENQ	MAX_CLIENTS
#define PORT	8888

static int listenfd;
struct sockaddr_in servaddr, cliaddr;
struct pollfd clients[MAX_CLIENTS];
static int nr_clients;
static int nready;

JNIEXPORT jint JNICALL
Java_poll_init(JNIEnv *, jclass)
{
	int i;

	printf("poll init.\n");
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	memset(clients, 0, sizeof(clients));

	clients[0].fd = listenfd;
	clients[0].events = POLLRDNORM;

	for (i = 1; i < MAX_CLIENTS; ++i)
		clients[i].fd = -1;

	nr_clients = 0;
	nready = 0;
}

static void try_add_client(void)
{
	socklen_t clilen;
	int i, connfd;

	if (clients[0].revents & POLLRDNORM) {
		clilen = sizeof(cliaddr);
		printf("\naccept connection~\n");

		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if (connfd < 0) {
			perror("accept error\n");
			exit(1);
		}

		printf("accept a new client: %s: %d\n",
				inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);

		for (i = 1; i < MAX_CLIENTS; ++i) {
			if (clients[i].fd < 0) {
				clients[i].fd = connfd;
				break;
			}
		}

		if (MAX_CLIENTS == i) {
			perror("too many connection\n");
			exit(1);
		}

		clients[i].events = POLLRDNORM;

		if (i > nr_clients)
			nr_clients = i;

		--nready;
		clients[0].revents ^= POLLRDNORM;
	}
}

static int find_ready_clientfd(void)
{
	int i, sockfd = -1;

	for (i = 1; i <= nr_clients; ++i) {
		if ((sockfd = clients[i].fd) < 0)
			continue;

		if (clients[i].revents & (POLLRDNORM | POLLERR)) {
			clients[i].revents ^= POLLRDNORM | POLLERR;
			if (--nready <= 0)
				break;
			break;
		}
	}
	return sockfd;
}

JNIEXPORT jint JNICALL
Java_poll_poll(JNIEnv *env, jclass jcl, jint in)
{
	int timeout = (int)in;
	int clientfd = -1;

	printf("poll poll, timeout=%d,nready=%d.\n", timeout, nready);

	while (nready >= 0) {
		try_add_client();
		clientfd = find_ready_clientfd();
		if (clientfd > 0)
			break;
		else if (clientfd <= 0)
			nready = poll(clients, nr_clients + 1, timeout);
	}

	return clientfd;
}

JNIEXPORT jint JNICALL
Java_poll_echo(JNIEnv *env, jclass jcl, jint in)
{
	int clientfd = (int)in;
	char buf[1024];
	int len;

	if (clientfd <= 0)
		return 0;

	printf("poll echo, clientfd=%d\n", clientfd);
	len = read(clientfd, buf, 1024);
	if (len <= 0) {
		close(clientfd);
	}
	write(clientfd, buf, len);
	return len;
}

#ifdef __cplusplus
}
#endif
#endif
