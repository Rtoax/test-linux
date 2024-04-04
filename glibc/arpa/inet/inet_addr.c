#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(void)
{
	int32_t addr;
	char lo[] = "127.0.0.1";

	printf("inet_addr: %d\n", inet_addr(lo));

	/* Wrong */
	addr = inet_addr("192.168.8.256");
	if (addr == INADDR_NONE)
		printf("Error occured!\n");

	return 0;
}

