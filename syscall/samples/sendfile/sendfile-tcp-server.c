#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, const char *argv[])
{
	char *ip;
	int port;
	char *file_name;
	int sock, connfd, ret;
	struct stat stat_buf;
	int filefd;
	struct sockaddr_in address;
	struct sockaddr_in client;

	ip = "127.0.0.1";
	port = 12345;
	file_name = "/etc/os-release";

	printf("Start tcp server on %s:%d\n", ip, port);
	printf("Test with $ nc %s %d\n", ip, port);

	filefd = open(file_name, O_RDONLY);
	assert(filefd > 0);

	fstat(filefd, &stat_buf);

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port   = htons(port);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	assert(sock > 0);

	ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, 5);
	assert(ret != -1);

	socklen_t client_addrlength = sizeof(client);

	connfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
	if (connfd < 0) {
		fprintf(stderr, "accept error! errno:%d, errstr:%s\n", errno, strerror(errno));
		exit(1);
	}

	sendfile(connfd, filefd, NULL, stat_buf.st_size);

	close(connfd);
	close(filefd);
	close(sock);
	return 0;
}

