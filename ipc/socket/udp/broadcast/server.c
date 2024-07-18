#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERVER_PORT 8000
#define MAXLINE 1500

#define BROADCAST_IP "10.170.6.255"
#define CLIENT_PORT 9000

int main(void)
{
	int sockfd;
	int i = 0;
	int flag = 1;
	struct sockaddr_in serveraddr, clientaddr;
	char buf[MAXLINE];

	/* 构造用于UDP通信的套接字 */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVER_PORT);

	bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));

	bzero(&clientaddr, sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	inet_pton(AF_INET, BROADCAST_IP, &clientaddr.sin_addr.s_addr);
	clientaddr.sin_port = htons(CLIENT_PORT);

	while (1) {
		sprintf(buf, "Drink %d glasses of water\n", i++);
		printf("Broadcast: %s\n", buf);
		//fgets(buf, sizeof(buf), stdin);
		sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
		sleep(1);
	}
	close(sockfd);
	return 0;
}

