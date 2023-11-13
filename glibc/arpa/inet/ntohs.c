#include <stdio.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	printf("%x\n", ntohs(0x1234));
	return 0;
}
