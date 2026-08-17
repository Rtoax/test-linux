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
	struct sockaddr_mctp addr, client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char buf[256];
	ssize_t n;

	/* 1. create MCTP socket */
	sockfd = socket(AF_MCTP, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* 2. Listen EID, recieve any message type */
	memset(&addr, 0, sizeof(addr));
	addr.smctp_family = AF_MCTP;
	addr.smctp_network = NET_ID;
	addr.smctp_addr.s_addr = EID;
	addr.smctp_type = MCTP_MSG_TYPE_ANY;
	addr.smctp_tag = TAG;

	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	printf("MCTP server listening on EID 8...\n");

	/* 3. Received msg and reply */
	while (1) {
		n = recvfrom(sockfd, buf, sizeof(buf) - 1, 0,
			     (struct sockaddr *)&client_addr, &client_addr_len);
		if (n < 0) {
			perror("recvfrom");
			break;
		}
		buf[n] = '\0';
		printf("Received from EID %d, type 0x%02x: %s\n",
		       client_addr.smctp_addr.s_addr, client_addr.smctp_type,
		       buf);

		const char *reply = "Hello from server";
		if (sendto(sockfd, reply, strlen(reply), 0,
			   (struct sockaddr *)&client_addr,
			   client_addr_len) < 0) {
			perror("sendto");
			break;
		}
	}

	close(sockfd);
	return 0;
}
