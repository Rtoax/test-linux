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

char *remote_addr = NULL;

int client_cmd_fn(char cmd, int *_errno)
{
	/**
	 * You MUST need ensure dangerous CMD
	 *	b - reboot
	 *	c - Crash
	 *	e - terminate all tasks
	 *	o - poweroff
	 *	u - unmount
	 */
	if (cmd == 'b' || cmd == 'c' || cmd == 'e' || cmd =='o' || cmd == 'u') {
		int yes = '\n';
		while (yes == '\n' || (yes != 'Y' && yes != 'N')) {
			printf("Crash trigger to %s, are you sure?[Y/N] ", remote_addr);
			yes = getchar();
			switch (yes) {
			case 'Y':
				goto done;
				break;
			case 'N':
				/* Operation not permitted */
				*_errno = -EPERM;
				return -1;
			default:
				printf("\n");
				break;
			}
		}
	}
done:
	*_errno = 0;
	return 0;
}

int client_writefile_fn(char *line, int *_errno)
{
	*_errno = 0;
	return 0;
}

int main(int argc, char *argv[])
{
	int _errno = 0;
	CMD_TYPE cmd_type = CMD_NONE;
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2) {
		perror("usage: tcpcli <IP address>");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	remote_addr = argv[1];
	if (inet_pton(AF_INET, remote_addr, &servaddr.sin_addr) < 0) {
		printf("inet_pton error for %s\n", remote_addr);
		exit(1);
	}

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(1);
	}

	char sendline[MAX_LINE], recvline[MAX_LINE];

	printf("CMD>> ");
	while (fgets(sendline, MAX_LINE, stdin) != NULL) {
		int ret = -1;
		ret = parse_cmd(sendline, client_cmd_fn, client_writefile_fn, &cmd_type, &_errno);
		if (ret != 0) {
			printf("CMD>> ");
			continue;
		}
		write(sockfd, sendline, strlen(sendline));

		/* crash, no need to recv response */
		if (sendline[0] != 'c') {
			read(sockfd, recvline, MAX_LINE);
		} else {
			printf("Server Crashed. Byebye.\n");
			goto byebye;
		}

		printf("  %s\n", recvline);
		printf("CMD>> ");
	}

byebye:
	close(sockfd);
	return 0;
}
