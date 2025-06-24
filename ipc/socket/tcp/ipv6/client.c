#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "common.h"

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in6 servaddr;
	char sendline[MAX_LINE], recvline[MAX_LINE];

	if (argc != 2) {
		perror("usage: tcpcli <IP address>");
		exit(1);
	}

	if ((sockfd = tcpsocket_client(argv[1])) == -1) {
		perror("socket error");
		exit(1);
	}

	(void)servaddr;

	printf("Input: ");
	while(fgets(sendline, MAX_LINE, stdin) != NULL) {
		write(sockfd, sendline, strlen(sendline));
		read(sockfd, recvline, MAX_LINE);
		printf("Client: %s\n", recvline);
		printf("Input: ");
	}

	close(sockfd);

	return 1;
}
