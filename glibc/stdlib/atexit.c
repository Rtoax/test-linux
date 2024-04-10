#include <stdio.h>
#include <stdlib.h>

void exit_callback(void)
{
	printf("Call back.\n");
}

int main(void)
{
	atexit(exit_callback);
	return 0;
}
