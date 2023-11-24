#include <stdio.h>

#ifdef ERROR
#pragma GCC poison printf
#endif

int main(void)
{
	printf("Hello\n");
	return 0;
}
