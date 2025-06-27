#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

const int SERV_PORT = 6000;
const int MAXLINE = 2048;

void dg_cli(FILE *fp, int sockfd, const struct  sockaddr *pservaddr,
	    socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen) < 0) {
			perror("sendto error");
			exit(1);
		}
		if ((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
			perror("recvfrom error");
			exit(1);
		}
		recvline[n] = '\0';
		fputs(recvline, stdout);
	}
}

int main(int argc, char *argv[])
{
	int sockfd, t;
	struct sockaddr_in servaddr;

	if (argc != 2) {
		perror("Usage: udpcli <IPAddress>");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	if ((t = inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0) {
		perror("inet_pton error");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket error");
		exit(1);
	}

	dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	return 0;
}
