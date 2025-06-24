#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "common.h"


int main(int argc ,char* argv[])
{
	int sock;
	struct sockaddr_in addr;
	int time_live;
	FILE* fp;
	char buf[BUF_SIZE];
	const int loopback = 0;

	if (argc != 2) {
		printf("Usage: %s <addr>\n", argv[0]);
		exit(1);
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock==-1) {
		error_handling("socket error");
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(PORT);

	setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopback,
		   sizeof(loopback));

	/* 设置生存时间为64，也就是最多经过64个路由器的转发 */
	time_live = 64;
	setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&time_live,
		   sizeof(time_live));

	fp = fopen("/etc/os-release", "r");
	if (fp == NULL)
		error_handling("fopen error");

	while (!feof(fp)) {
		fgets(buf, BUF_SIZE, fp);
		sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&addr,
			sizeof(addr));
		sleep(1);
	}

	fclose(fp);
	close(sock);
	return 0;
}
