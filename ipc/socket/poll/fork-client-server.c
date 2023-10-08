#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <poll.h>

#define MAXBUF 256
#define LISTENQ	5

void child_process(void)
{
	/* Give server some time to start up */
	sleep(2);

	char msg[MAXBUF];
	struct sockaddr_in addr = {0};
	int sockfd, num=1;
	srandom(getpid());

	/* Create socket and connect to server */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	printf("child {%d} connected \n", getpid());
	while (1) {
		int sl = (random() % 10 ) +  1;
		num++;
		sleep(sl);
		sprintf(msg, "Test message %d from client %d", num, getpid());
		/* Send message */
		write(sockfd, msg, strlen(msg));
	}
}

int main(void)
{
	char buffer[MAXBUF];
	struct sockaddr_in addr;
	struct sockaddr_in client;
	socklen_t addrlen;
	int i;
	int sockfd;
	struct pollfd pollfds[LISTENQ];

	for (i = 0; i < LISTENQ; i++) {
		if (fork() == 0) {
			child_process();
			exit(0);
		}
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&addr, 0, sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&addr ,sizeof(addr));

	listen(sockfd, LISTENQ);

	for (i = 0;i < LISTENQ; i++) {
		memset(&client, 0, sizeof (client));
		addrlen = sizeof(client);
		pollfds[i].fd = accept(sockfd,(struct sockaddr*)&client, &addrlen);
		pollfds[i].events = POLLIN;
	}

	sleep(1);

	while (1) {
		do{
			puts("round again");
			poll(pollfds, LISTENQ, 50000);
		} while (errno == EINTR);

		for (i = 0; i < LISTENQ; i++) {
			if (pollfds[i].revents & POLLIN) {
				pollfds[i].revents = 0;
				memset(buffer,0,MAXBUF);
				read(pollfds[i].fd, buffer, MAXBUF);
				puts(buffer);
			}
		}
	}

	return 0;
}
