#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void handler(int i)
{
	printf("handler: get abort SIGABRT\n");
	exit(EXIT_FAILURE);
}

int main(void)
{
	signal(SIGABRT, handler);
	abort();
	return 0;
}
