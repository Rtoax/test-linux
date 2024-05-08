#include <stdio.h>
#include <stdlib.h>

void bye(int status, void *arg)
{
	puts("Goodbye, cruel world....");
}

int main(void)
{
	on_exit(bye, NULL);
	exit(EXIT_SUCCESS);
}
