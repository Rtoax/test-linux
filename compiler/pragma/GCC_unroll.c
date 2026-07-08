#include <stdio.h>

int main(void)
{
	int i, n = 10;

	#if __GNUC__ >= 8
	#pragma GCC unroll 10
	#elif defined(__clang__)
	/* 'enable', 'full' or 'disable' */
	#pragma clang loop unroll (enable)
	#endif
	for (i = 0; i < n; i++)
		printf("%d\n", i);

	#if defined(__clang__)
	#pragma clang loop unroll (disable)
	#endif
	for (i = 0; i < n; i++)
		printf("%d\n", i);

	return 0;
}
