#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		printf("usage: %s [ip]\n", argv[0]);
		return 1;
	}

	const char *ip = argv[1];
	int port = 8888;
	int sockfd;
	struct sockaddr_in server_address;

	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_address.sin_addr);
	server_address.sin_port = htons(port);

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0 && "socket failed.");

	if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0 ) {
		printf( "connection failed\n" );
		exit(1);
	}

	printf( "send oob data out\n" );
	const char *oob_data = "abc";
	const char *normal_data = "123";

	/* 发送带外数据 */
	send(sockfd, normal_data, strlen(normal_data), 0);
	send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
	send(sockfd, normal_data, strlen(normal_data), 0);

	close(sockfd);
	return 0;
}

