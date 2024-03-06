/**
 * 统一事件源：使信号事件可以其他IO事件一样被处理
 *
 * - 把信号的主要逻辑放到程序的主循环中
 * - 当信号处理函数被触发时，它只是简单的通知主循环程序接收到信号
 * - 并把信号值传递给主循环，主循环根据接收到的信号值执行目标信号的对应逻辑代码
 *
 * client: nc 127.0.0.1 8888
 *
 * 2018-06-30	Rong Tao	Create this.
*/
#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define port 8888
#define MAX_EVENT_NUMBER 1024
#define MAXDATASIZE 1024

static int sopairfd[2];

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void epoll_addfd(int epollfd, int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

void sig_handler(int sig)
{
	int save_errno = errno;
	int msg = sig;
	send(sopairfd[1], (char*)&msg, 1, 0);
	errno = save_errno;
}

void addsig(int sig)
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
	int ret = 0;
	int epollfd, listenfd;
	struct sockaddr_in address;
	bool stop_server = false;
	struct epoll_event events[MAX_EVENT_NUMBER];

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	listenfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(listenfd >= 0);

	int nReuseAddr = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &nReuseAddr, sizeof(nReuseAddr));

	ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
	if (ret == -1) {
		printf("errno is %d\n", errno);
		return -errno;
	}

	ret = listen(listenfd, 5);
	assert(ret != -1);

	epollfd = epoll_create(5);
	assert(epollfd != -1);

	epoll_addfd(epollfd, listenfd);

	ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sopairfd);
	assert(ret != -1);

	setnonblocking(sopairfd[1]);
	epoll_addfd(epollfd, sopairfd[0]);

	addsig(SIGHUP);
	addsig(SIGCHLD);
	addsig(SIGTERM);
	addsig(SIGINT);

	while (!stop_server) {
		int i, j;
		int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		if ((number < 0) && (errno != EINTR)) {
			printf("epoll failure\n");
			break;
		}

		for (i = 0; i < number; i++) {
			int sockfd = events[i].data.fd;

			/* Handle connection */
			if (sockfd == listenfd) {
				struct sockaddr_in caddr;
				socklen_t caddrlen = sizeof(caddr);
				int connfd = accept(listenfd,
						    (struct sockaddr*)&caddr,
						    &caddrlen);
				send(connfd, "input>> ", sizeof("input>> "), 0);
				epoll_addfd(epollfd, connfd);
			/* Handle signal */
			} else if((sockfd == sopairfd[0]) && (events[i].events & EPOLLIN)) {
				char signals[1024];
				ret = recv(sopairfd[0], signals, sizeof(signals), 0);
				if (ret == -1 || ret == 0)
					continue;

				for (j = 0; j < ret; ++j) {
					printf("I caugh the signal %d\n", signals[j]);
					switch (signals[j]) {
					case SIGCHLD:
					case SIGTERM:
					case SIGHUP:
					{
						continue;
					}
					/* Ctrl-C */
					case SIGINT:
					{
						int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, sockfd, NULL);
						if (ret == -1) {
							perror("epoll_ctl error!\n");
							exit(1);
						}

						close(sockfd);
						stop_server = true;
					}
					}
				}
			/* Handle client: echo client */
			} else {
				char buf[MAXDATASIZE];
				memset(buf, 0, sizeof(buf));
				int numbytes = recv(sockfd, buf, MAXDATASIZE, 0);
				if (numbytes > 0) {
					send(sockfd, buf, numbytes, 0);
				}
				send(sockfd, "input>> ", sizeof("input>> "), 0);
			}
		}
	}

	printf("close fds\n");
	close(listenfd);
	close(sopairfd[1]);
	close(sopairfd[0]);
	return 0;
}
