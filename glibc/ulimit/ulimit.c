#include <stdio.h>
#include <ulimit.h>

int main(void)
{
	long fs;

	fs = ulimit(UL_GETFSIZE, 0);
	printf("%ld\n", fs);

	ulimit(UL_SETFSIZE, 1024 * 1024 * 1024);

	fs = ulimit(UL_GETFSIZE, 0);
	printf("%ld\n", fs);

	return 0;
}
