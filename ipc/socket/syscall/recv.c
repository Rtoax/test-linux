#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <strings.h>

#define PORT 21
#define REMOTE_IP "127.0.0.1"

int main(void)
{
	int s;
	struct sockaddr_in addr;
	char mybuffer[256];

	s = socket(AF_INET, SOCK_STREAM, 0);

	bzero((struct sockaddr*)&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(REMOTE_IP);

	connect(s, (struct sockaddr*)&addr, sizeof(addr));

	recv(s, mybuffer, sizeof(mybuffer), 0);

	printf("mybuffer: %s\n", mybuffer);

	return 0;
}
