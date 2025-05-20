#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>

#include "config.h"

int main(void)
{
	int sockfd, client_fd;
	struct sockaddr_vm addr = {0};
	char buf[1024];

	if ((sockfd = socket(AF_VSOCK, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	addr.svm_family = AF_VSOCK;
	addr.svm_cid = CID_HOST;
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
