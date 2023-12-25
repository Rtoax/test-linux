#include <stdio.h>
#include <signal.h>
#include <string.h>


int main(void)
{
	printf("SIGTRAP: %s\n", strsignal(SIGTRAP));
	return 0;
}

