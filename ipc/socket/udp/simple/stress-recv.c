#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <unistd.h>


const int SERV_PORT = 6000;
const int MAXLINE = 2048;

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[MAXLINE];
	size_t n, recvcnt, recvbytes;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket error");
		exit(1);
	}

	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
		perror("bind error");
		exit(1);
	}

	len = sizeof(cliaddr);

	recvcnt = recvbytes = 0;

	for (;;) {
		n = recvfrom(sockfd, mesg, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
		if (n < 0)
			continue;

		recvcnt++;
		recvbytes += n;
		printf("recv %ld pkts, %ld bytes.\n", recvcnt, recvbytes);
	}

	close(sockfd);
	return 0;
}

