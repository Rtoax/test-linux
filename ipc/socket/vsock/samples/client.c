#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>

#include "config.h"
#include "../vsock_helpers.h"

int main(void)
{
	unsigned int cid;
	int sockfd;
	struct sockaddr_vm addr = {0};
	const char *msg = "Hello from VSOCK client!";

	if ((sockfd = socket(AF_VSOCK, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	cid = vsock_get_local_cid();

	printf("CID %d\n", cid);

	addr.svm_family = AF_VSOCK;
	addr.svm_cid = CID_HOST;
	addr.svm_port = PORT;

	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("connect");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	if (write(sockfd, msg, strlen(msg)) < 0) {
		perror("write");
	} else {
		printf("Message sent\n");
	}

	close(sockfd);
	return 0;
}
