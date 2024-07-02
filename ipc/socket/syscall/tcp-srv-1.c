#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define PORT 5678
#define MAX 10

void sig_handler(int sig)
{
	switch (sig) {
	case SIGINT:
		printf("catch ctrl-c.\n");
		break;
	}
}

int main(void)
{
	int sockfd, newsockfd;

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	signal(SIGINT, sig_handler);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	listen(sockfd, MAX);

	newsockfd = accept(sockfd, (struct sockaddr *)&addr, &addr_len);
	/**
	 * FIXME: 在多进程服务器编写时候，父进程accept，但是会遇到EINTR错误：
	 * 父进程接收链接请求，accept 阻塞的时候被信号中断，处理信号对应的操作
	 * 之后，回来之后不阻塞了，直接返回 -1 ，这时候 errno == EINTR。
	 *
	 * TODO: 如何测试？
	 */
	while (newsockfd == -1 && errno == EINTR)
		newsockfd = accept(sockfd, (struct sockaddr *)&addr, &addr_len);

	printf("Get new client.\n");

	close(newsockfd);
	close(sockfd);
	exit(0);
}
