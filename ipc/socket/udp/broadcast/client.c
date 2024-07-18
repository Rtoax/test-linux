#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 8000
#define MAXLINE 4096
#define CLIENT_PORT 9000

int main(int argc, char *argv[])
{
	struct sockaddr_in localaddr;
	int ret, confd;
	ssize_t len;
	char buf[MAXLINE];

	confd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0" , &localaddr.sin_addr.s_addr);
	localaddr.sin_port = htons(CLIENT_PORT);

	ret = bind(confd, (struct sockaddr *)&localaddr, sizeof(localaddr));
	if (ret == 0)
		printf("...bind ok...\n");

	while (1) {
		len = recvfrom(confd, buf, sizeof(buf), 0, NULL, 0);
		write(STDOUT_FILENO, buf, len);
	}
	close(confd);

	return 0;
}


