#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	struct in_addr in;

	/* 127.0.0.1 */
	in.s_addr = 16777343;
	printf("inet_ntoa: %s\n", inet_ntoa(in));

	return 1;
}

