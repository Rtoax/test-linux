#include <stdio.h>

#pragma GCC poison printf

int main(void)
{
	printf("Hello\n");
	return 0;
}
