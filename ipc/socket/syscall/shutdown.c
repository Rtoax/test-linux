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
	int sockfd, newsockfd, ret;
	char buf[64];

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	listen(sockfd, MAX);

	printf("Getting new client, $ nc 0.0.0.0 %d\n", PORT);

	newsockfd = accept(sockfd, (struct sockaddr *)&addr, &addr_len);

	printf("Get new client.\n");

	while (1) {
		while ((ret = read(newsockfd, buf, sizeof(buf))) > 0) {
			ret = write(newsockfd, "hello", 5);
			if (ret <= 0)
				perror("write: ");

			/**
			 * how: SHUT_WR, SHUT_RD, SHUT_RDWR
			 * Cause: Ncat: Broken pipe.
			 */
			shutdown(newsockfd, SHUT_RDWR);
		}
		break;
	}

	close(newsockfd);
	close(sockfd);
	exit(0);
}
