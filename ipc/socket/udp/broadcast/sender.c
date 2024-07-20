#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 1235
#define BUF_SIZE 30

void error_handling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc,char* argv[])
{
	int sock;
	struct sockaddr_in addr;
	char message[BUF_SIZE];
	int so_brd = 1;
	FILE* fp;

	if (argc < 2) {
		fprintf(stderr, "%s [IP]\n", argv[0]);
		exit(1);
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(PORT);

	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *)&so_brd,
		   sizeof(so_brd));

	fp = fopen("/etc/os-release", "r");
	if (fp == NULL)
		error_handling("fopen error");

	while (!feof(fp)) {
		fgets(message, BUF_SIZE, fp);
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		sendto(sock, message, BUF_SIZE, 0, (struct sockaddr *)&addr,
			sizeof(addr));
	}

	fclose(fp);
	close(sock);
	return 0;
}

