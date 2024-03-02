#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5678
#define MAX 10

int main(void)
{
	int sockfd, newsockfd;

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	listen(sockfd, MAX);

	newsockfd = accept(sockfd, (struct sockaddr *)&addr, &addr_len);

	printf("Get new client.\n");

	close(newsockfd);
	close(sockfd);
	exit(0);
}
