#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>
#include <termios.h>


int main(int argc, char *argv[])
{
	printf("tcgetsid = %d\n", tcgetsid(fileno(stdin)));
	printf("getsid = %d\n", getsid(getpid()));
	return 0;
}
