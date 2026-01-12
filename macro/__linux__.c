#include <stdio.h>
#include <stdlib.h>

int main(void)
{
#ifdef __linux__
	printf("__linux__ %d\n", __linux__);
#endif
	return 0;
}
