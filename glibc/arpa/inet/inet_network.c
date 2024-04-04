#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
	printf("0x%x\n", inet_network("127.0.0.1"));

	return 0;
}
