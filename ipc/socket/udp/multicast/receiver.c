#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "common.h"


int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in addr;
	char buf[BUF_SIZE];
	int str_len;
	struct ip_mreq join_addr;
	const int loopback = 0;

	if (argc < 2) {
		fprintf(stderr, "%s [IP]\n", argv[0]);
		exit(1);
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopback,
		   sizeof(loopback));

	join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);
	join_addr.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&join_addr,
		   sizeof(join_addr));

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		error_handling("bind error");

	while (1) {
		str_len = recvfrom(sock, buf, BUF_SIZE - 1, 0, NULL, 0);
		if(!str_len)
			break;
		buf[str_len] = 0;
		fputs(buf, stdout);
	}
	close(sock);
	return 0;
}
