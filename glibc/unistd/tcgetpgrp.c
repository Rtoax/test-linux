#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	printf("tcgetpgrp = %d\n", tcgetpgrp(fileno(stdin)));

	return 0;
}
