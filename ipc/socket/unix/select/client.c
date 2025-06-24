#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "common.h"

int connect_fd;

void handle_sigint(int signum)
{
	printf("Catch the SIGINT signal.\n");
	send(connect_fd, GOODBYE, 8, 0);
	close(connect_fd);
	exit(1);
}

int main(void)
{
	int ret = 0;
	struct sockaddr_un srv_addr;

	char msg[256] = HELLO;
	int msglen = 0;

	signal(SIGINT, handle_sigint);

	connect_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (connect_fd < 0) {
		perror("create socket error.");
		exit(1);
	}

	srv_addr.sun_family = AF_UNIX;
	strcpy(srv_addr.sun_path, PATH);

	ret = connect(connect_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret == -1) {
		perror("connect error");
		close(connect_fd);
		exit(1);
	}

	while (1) {
		send(connect_fd, msg, 8, 0);

		memset(msg, 0 , sizeof(msg));
		msglen = recv(connect_fd, msg, sizeof(msg), 0);

		printf("%s %d\n", msg, msglen);

		memset(msg, 0 , sizeof(msg));
		printf("Input: ");
		scanf("%s", msg);

		if (strcmp((char*)msg, QUIT) == 0) {
			raise(SIGINT);
		}
	}

	close(connect_fd);
	return 0;
}
