#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#define PORT 8888
#define MAX_LINE 2048

int max(int a, int b)
{
	return a > b ? a : b;
}

ssize_t readline(int fd, char *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;

	for (n = 1; n < maxlen; n++) {
		if ((rc = read(fd, &c, 1)) == 1) {
			*ptr++ = c;
			if (c == '\n') {
				/*newline is stored, like fgets()*/
				break;
			}
		} else if(rc == 0) {
			*ptr = 0;
			/*EOF, n-1 bytes were read */
			return n - 1;
		} else {
			/*error, errno set by read()*/
			return -1;
		}
	}
	/*NULL terminate like fgets()*/
	*ptr = 0;
	return n;
}

void str_cli(int sockfd)
{
	char sendline[MAX_LINE], recvline[MAX_LINE];

	while (fgets(sendline, MAX_LINE, stdin) != NULL) {
		write(sockfd, sendline, strlen(sendline));

		bzero(recvline, MAX_LINE);

		if (readline(sockfd, recvline, MAX_LINE) == 0) {
			perror("server terminate prematurely");
			exit(1);
		}
		if (fputs(recvline, stdout) == EOF) {
			perror("fputs error");
			exit(1);
		}

		bzero(sendline, MAX_LINE);
	}
}

void str_cli2(FILE *fp, int sockfd)
{
	int maxfd;
	fd_set rset;

	char sendline[MAX_LINE], recvline[MAX_LINE];

	FD_ZERO(&rset);

	while (1) {
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfd = max(fileno(fp), sockfd) + 1;
		select(maxfd, &rset, NULL, NULL, NULL);

		if (FD_ISSET(fileno(fp), &rset)) {
			if (fgets(sendline, MAX_LINE, fp) == NULL) {
				printf("read nothing~\n");
				close(sockfd);/*all done*/
				return;
			}

			sendline[strlen(sendline) - 1] = '\0';
			write(sockfd, sendline, strlen(sendline));
		}

		if (FD_ISSET(sockfd, &rset)) {
			if (readline(sockfd, recvline, MAX_LINE) == 0) {
				perror("handleMsg: server terminated prematurely.\n");
				exit(1);
			}

			if (fputs(recvline, stdout) == EOF) {
				perror("fputs error");
				exit(1);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int sockfd;

	struct sockaddr_in servaddr;

	if (argc != 2) {
		perror("Usage: tcpip <IPAddress>");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0) {
		printf("inet_port error for %s\n", argv[1]);
		exit(1);
	}

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(1);
	}

	str_cli(sockfd);

	return 0;
}

