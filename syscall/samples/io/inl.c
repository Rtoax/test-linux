#include <unistd.h>
#include <stdio.h>
#include <sys/io.h>
#include <stdlib.h>

void usage(void)
{
	printf("Usage: inl <port>\n\r");
	printf("  e.g. inl 0x20e \n\r");
}

int main(int argc, char* argv[])
{
	char *p;
	unsigned long int port;
	unsigned int value;

	if (argc != 2) {
		usage();
		return 1;
	}

	port   = strtoul(argv[1], &p, 16);
	port  &= 0x3ff;

	printf("Port: 0x%04x\n\r", (unsigned int)port);

	if (ioperm(port, 4, 1) < 0) {
		perror("Permisson: ioperm");
		return 2;
	}

	value = inl((unsigned short int)port);
	value &= 0xffffffff;

	printf("0x%08x\n\r", value);

	return 0;
}
