#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>

#include "config.h"
#include "../vsock_helpers.h"

int main(int argc, char *argv[])
{
	unsigned int cid, remote_cid;
	int sockfd;
	struct sockaddr_vm addr = {0};
	const char *msg = "Hello from VSOCK client!";

	if ((sockfd = socket(AF_VSOCK, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	cid = vsock_get_local_cid();

	printf("Local CID %d(%s)\n", cid, vsock_cid_name(cid));

	remote_cid = vsock_get_cid_from_args(argc, argv);
	if (remote_cid == 0)
		remote_cid = VMADDR_CID_HOST;

	printf("Remote CID %d(%s)\n", remote_cid, vsock_cid_name(remote_cid));

	addr.svm_family = AF_VSOCK;
	addr.svm_cid = remote_cid;
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
