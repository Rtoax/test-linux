#include <stdio.h>

int main(void)
{
	int i, n = 10;

	#if __GNUC__ >= 8
	#pragma GCC unroll 10
	#endif
	for (i = 0; i < n; i++)
		printf("%d\n", i);

	return 0;
}
