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
	int sockfd, client_fd;
	struct sockaddr_vm addr = {0};
	char buf[1024];

	if ((sockfd = socket(AF_VSOCK, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	cid = vsock_get_local_cid();

	printf("CID %d\n", cid);

	addr.svm_family = AF_VSOCK;
	addr.svm_cid = VMADDR_CID_ANY;
	addr.svm_port = PORT;

	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 5) < 0) {
		perror("listen");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	printf("Server waiting for connection...\n");

	if ((client_fd = accept(sockfd, NULL, NULL)) < 0) {
		perror("accept");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	ssize_t len = read(client_fd, buf, sizeof(buf)-1);
	if (len < 0) {
		perror("read");
	} else {
		buf[len] = '\0';
		printf("Received: %s\n", buf);
	}

	close(client_fd);
	close(sockfd);
	return 0;
}
