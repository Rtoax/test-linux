#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void sig_handler(int sig)
{
	switch (sig) {
	case SIGBUS:
		printf("Catch SIGBUS.\n");
	default:
		break;
	}
	exit(1);
}

/**
 * Only trigger SIGBUS on special architecture.
 */

void demo1(void)
{
	unsigned int i = 0x12345678;
	unsigned short int *q = NULL;
	unsigned char *p = (unsigned char *)&i;

	*p = 0x00;
	q  = (unsigned short int *)(p + 1);
	*q = 0x0000;

}

void demo2(void)
{
	unsigned int i = 0x12345678;
	unsigned short int j = 0x0000;

	j = *(( unsigned short int *)(((unsigned char *)&i) + 1));
	(void)j;
}

int main(int argc, char *argv[])
{
	signal(SIGBUS, sig_handler);
	demo1();
	demo2();
	return EXIT_SUCCESS;
}

