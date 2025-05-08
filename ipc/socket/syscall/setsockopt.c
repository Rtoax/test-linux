#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


#define BUFFER_SIZE   1024

int main(int argc, const char *argv[])
{
	const char *ip = "127.0.0.1";
	int sock, option;
	int port = 1234;
	char recvbuf[BUFFER_SIZE], sendbuf[BUFFER_SIZE];
	struct sockaddr_in address, client;
	socklen_t len, optlen;
	int ret, connfd;


	bzero(&address, sizeof(address));

	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	len = sizeof(recvbuf);

	option = 1;
	optlen = sizeof(option);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, optlen);

	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
	printf("the tcp receive buffer set to %p\n", &recvbuf);
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t *)&len);
	printf("the tcp receive buffer size after setting is %d\n", len);

	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
	printf("the tcp send buffer set to %p\n", &sendbuf);
	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *)&len);
	printf("the tcp send buffer size after setting is %d\n", len);

	ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, 5);
	assert(ret != -1);

	len = sizeof(client);
	connfd = accept(sock, (struct sockaddr *)&client, &len);
	if (connfd < 0) {
		printf("errno is:  %d, errstr:%s\n", errno, strerror(errno));
	} else {
		char buffer[BUFFER_SIZE];
		memset(buffer, '\0', BUFFER_SIZE);
		while (recv(connfd, buffer, BUFFER_SIZE, 0) > 0);
		close(connfd);
		char client_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, (void *)&client.sin_addr, client_ip, (socklen_t )INET_ADDRSTRLEN);
		printf("Recv data from %s, data content is:%s\n", client_ip, buffer);
	}

	close(sock);
	return 0;
}
