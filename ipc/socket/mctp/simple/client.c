#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/mctp.h>
#include "common.h"

int main(void)
{
	int sockfd;
	struct sockaddr_mctp dest_addr, from_addr;
	socklen_t from_len = sizeof(from_addr);
	char buf[256];
	const char *msg = "Hello MCTP";
	ssize_t n;

	sockfd = socket(AF_MCTP, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.smctp_family = AF_MCTP;
	dest_addr.smctp_network = NET_ID;
	dest_addr.smctp_addr.s_addr = EID;
	dest_addr.smctp_type = 0x7f; // custom msg (avoid DMTF)
	dest_addr.smctp_tag = TAG;

	printf("Sending to EID 8: %s\n", msg);
	if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&dest_addr,
		   sizeof(dest_addr)) < 0) {
		perror("sendto");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	n = recvfrom(sockfd, buf, sizeof(buf) - 1, 0,
		     (struct sockaddr *)&from_addr, &from_len);
	if (n < 0) {
		perror("recvfrom");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	buf[n] = '\0';
	printf("Reply from EID %d, type 0x%02x: %s\n",
	       from_addr.smctp_addr.s_addr, from_addr.smctp_type, buf);

	close(sockfd);
	return 0;
}
