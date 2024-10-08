#include <stdio.h>

int main(void)
{
	int i, n = 10;

	# pragma GCC unroll 10
	for (i = 0; i < n; i++)
		printf("%d\n", i);

	return 0;
}
