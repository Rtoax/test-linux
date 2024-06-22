#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/un.h>

#include "VhostUserRequest.h"

#define BUF_SIZE 1024

/* https://qemu.readthedocs.io/en/latest/interop/vhost-user.html */
typedef struct VhostUserMsg {
	VhostUserRequest request;
	uint32_t flags;
	uint32_t size;

	union {
		uint64_t num;
	};
} __attribute__((packed)) VhostUserMsg;


int main(int argc, char *argv[])
{
	int sockfd, clientfd;
	struct sockaddr_un serv_addr,clnt_addr;
	socklen_t addr_sz;
	int len;
	char buf[BUF_SIZE];
	char *path;
	VhostUserMsg *msg;

	if (argc < 2) {
		fprintf(stderr, "%s [sock path]\n", argv[0]);
		exit(1);
	}

	path = argv[1];

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	serv_addr.sun_family = AF_UNIX;
	strncpy(serv_addr.sun_path, path, strlen(path) + 1);

	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("bind() error");
		return 1;
	}

	if (listen(sockfd, 1) == -1) {
		perror("listen() error");
		return 1;
	}

	addr_sz = sizeof(clnt_addr);

	clientfd = accept(sockfd, (struct sockaddr*)&clnt_addr, &addr_sz);
	if (clientfd==-1) {
		perror("accept() error");
		return 1;
	}

	while (1) {
		len = read(clientfd, buf, BUF_SIZE);
		if (len <= 0) {
			close(clientfd);
			break;
		}
		msg = (VhostUserMsg *)buf;

		printf("len = %d\n", len);
		printf("%d %d %d\n", msg->request, msg->flags, msg->size);

		switch (msg->request) {
		case VHOST_USER_GET_FEATURES:
			msg->request = VHOST_USER_SET_FEATURES;
			msg->flags = 0x3;
			msg->size = sizeof(msg->num);
			msg->num = 1ULL << 10;

			write(clientfd, msg, sizeof(struct VhostUserMsg));
			break;
		default:
			break;
		}
	}

	close(clientfd);
	close(sockfd);

	return 0;
}

