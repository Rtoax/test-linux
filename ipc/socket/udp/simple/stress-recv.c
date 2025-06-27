#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


const int SERV_PORT = 6000;
const int MAXLINE = 2048;
volatile size_t recvcnt, recvbytes;

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

void *display_thread(void *arg)
{
	size_t old_pkts = 0;
	while (1) {
		if (old_pkts != recvcnt) {
			printf("Total rx %ld pkts, %ld bytes.\n", recvcnt, recvbytes);
			old_pkts = recvcnt;
		}
		sleep(1);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[MAXLINE];
	size_t n;
	pthread_t displayer;

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

	pthread_create(&displayer, NULL, display_thread, NULL);

	for (;;) {
		n = recvfrom(sockfd, mesg, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
		if (n < 0)
			continue;

		__sync_add_and_fetch(&recvcnt, 1);
		__sync_add_and_fetch(&recvbytes, n);
	}

	pthread_join(displayer, NULL);
	close(sockfd);
	return 0;
}
