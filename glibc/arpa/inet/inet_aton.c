#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(void)
{
	struct sockaddr_in sockAddr;
	struct in_addr addr;

	inet_aton("192.168.8.54", &sockAddr.sin_addr);
	inet_aton("127.0.0.1", &addr);

	printf("%d\n", addr.s_addr);
	printf("%d\n", sockAddr.sin_addr.s_addr);

	return 0;
}
