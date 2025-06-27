#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>


const int SERV_PORT = 6000;
const int MAXLINE = 2048;
volatile sig_atomic_t keep_going = 1;

void sig_handler(int signum)
{
	psignal(signum, "Signal");
	keep_going = 0;
}

int main(int argc, char *argv[])
{
	int sockfd, t;
	struct sockaddr_in servaddr;
	struct sockaddr *pservaddr;
	size_t n, sendcnt, sendbytes, total;
	char sendline[MAXLINE];

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <IPAddress> <N pkts>\n", argv[0]);
		exit(1);
	}

	signal(SIGINT, sig_handler);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	if ((t = inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0) {
		perror("inet_pton error");
		exit(1);
	}

	/* default send 10000 packets */
	total = 10000;

	if (argc >= 3) {
		total = strtoul(argv[2], NULL, 10);
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket error");
		exit(1);
	}

	pservaddr = (struct sockaddr *)&servaddr;

	sendcnt = sendbytes = 0;

	printf("Try send %ld packets to %s\n", total, argv[1]);

	while (keep_going) {
		n = sendto(sockfd, sendline, MAXLINE, 0, pservaddr, sizeof(servaddr));
		if (n > 0) {
			sendcnt++;
			sendbytes += n;
		}

		if (sendcnt % 1000 == 0)
			printf("send %ld pkts, %ld bytes.\n", sendcnt, sendbytes);

		if (sendcnt == total)
			break;
	}

	printf("Total tx %ld pkts, %ld bytes\n", sendcnt, sendbytes);

	close(sockfd);
	return 0;
}
