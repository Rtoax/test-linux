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

int setsocktimeout(int sockfd, struct timeval *tv)
{
	int ret;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, tv, sizeof(struct timeval));
	if (ret) {
		perror("setsockopt error");
	}
	return ret;
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct timeval tv;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		exit(1);
	}

	/**
	 * errno = EDOM if tv_usec >= 10^6
	 * see kernel commit ba78073e6f70 ("[NET]: "wrong timeout value" in
	 * sk_wait_data() v2") kernel <= 2.6.22
	 */
	tv.tv_sec = 0;
	tv.tv_usec = 1500000;
	setsocktimeout(sockfd, &tv);
	if (errno != EDOM)
		fprintf(stderr, "Your kernel <= 2.6\n");

	/**
	 * Fix EDOM(Numerical argument out of domain) error
	 */
	tv.tv_sec = 1;
	tv.tv_usec = 500000;
	setsocktimeout(sockfd, &tv);

	close(sockfd);
	return 0;
}
