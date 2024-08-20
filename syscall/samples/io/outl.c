#include <unistd.h>
#include <stdio.h>
#include <sys/io.h>
#include <stdlib.h>

void usage(void)
{
	printf("Usage: outl <value> <port>\n\r");
	printf("  e.g. outl 0xa5a5a5a5 0x20e\n\r");
}

int main(int argc, char* argv[])
{
	char *p;
	unsigned long int port;
	unsigned long int value;

	if (argc != 3) {
		usage();
		return 1;
	}

	value  = strtoul(argv[1], &p, 16);
	value &= 0xffffffff;
	port   = strtoul(argv[2], &p, 16);
	port  &= 0x3ff;

	printf("Port: 0x%04x Value: 0x%02x\n", (unsigned int)port, (unsigned int)value);

	if (ioperm(port, 4, 1) < 0) {
		perror("Permisson: ioperm");
		return 2;
	}

	outl((unsigned int)value, (unsigned short int)port);

	return 0;
}
