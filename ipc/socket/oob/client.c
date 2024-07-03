#include <arpa/inet.h>
#include <assert.h>
#include <libgen.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>


/**
 * Whenever out-of-band data is received, there is an associated out-of-band mark.
 * This is the position in the normal stream of data at the sender when the sending
 * process sent the out-of-band byte. The receiving process determines whether or
 * not it is at the out-of-band mark by calling the sockatmark function while it
 * reads from the socket.
 */
static int sockcatmark(int fd)
{
	int ret, flag;

	ret = ioctl(fd, SIOCATMARK, &flag);
	if (ret < 0) {
		perror("ioctl: SIOCATMARK");
		return -1;
	}
	printf("SIOCATMARK = %d\n", flag);
	return 0;
}

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

	sockcatmark(sockfd);

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

