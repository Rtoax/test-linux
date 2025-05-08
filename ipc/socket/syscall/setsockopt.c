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
	struct sockaddr_in address, client;
	socklen_t len, optlen;
	int ret, connfd;
	char buffer[BUFFER_SIZE];
	char client_ip[INET_ADDRSTRLEN];
	int recvbuf_sz, sendbuf_sz;
	int err;

	bzero(&address, sizeof(address));

	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	option = 1;
	optlen = sizeof(option);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, optlen);

	recvbuf_sz = 1024 * 1024;
	err = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf_sz, sizeof(recvbuf_sz));
	if (err)
		perror("setsockopt SO_RCVBUF");
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &len, &optlen);
	printf("the tcp receive buffer size after setting is %d\n", len);

	sendbuf_sz = 1024 * 1024;
	err = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf_sz, sizeof(sendbuf_sz));
	if (err)
		perror("setsockopt SO_SNDBUF");
	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &len, &optlen);
	printf("the tcp send buffer size after setting is %d\n", len);

	ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, 5);
	assert(ret != -1);

	len = sizeof(client);
	connfd = accept(sock, (struct sockaddr *)&client, &len);
	if (connfd < 0) {
		printf("errno is:  %d, errstr:%s\n", errno, strerror(errno));
		goto exit;
	}

	memset(buffer, '\0', BUFFER_SIZE);
	while (recv(connfd, buffer, BUFFER_SIZE, 0) > 0);
	close(connfd);
	inet_ntop(AF_INET, (void *)&client.sin_addr, client_ip, (socklen_t)INET_ADDRSTRLEN);
	printf("Recv data from %s, data content is:%s\n", client_ip, buffer);

exit:
	close(sock);
	return 0;
}
