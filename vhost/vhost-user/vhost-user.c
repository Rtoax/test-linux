#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/un.h>

#define BUF_SIZE 1024


int main(int argc, char *argv[])
{
	int sockfd, clientfd;
	struct sockaddr_un serv_addr,clnt_addr;
	int addr_sz, len;
	char buf[BUF_SIZE];
	char *path;

	if (argc < 2) {
		fprintf(stderr, "%s [sock path]\n", argv[0]);
		exit(1);
	}

	path = argv[1];

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	serv_addr.sun_family = AF_UNIX;
	strncpy(serv_addr.sun_path, path, strlen(path));

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
		printf("len = %d\n", len);
	}

	close(clientfd);
	close(sockfd);

	return 0;
}

