/**
 * clang lang loop unroll could be 'enable', 'full' or 'disable'
 */
#include <stdio.h>

void origin(void)
{
	int i, n = 10;

	for (i = 0; i < n; i++)
		printf("%d\n", i);
}

void enable(void)
{
	int i, n = 10;

	#if defined(__clang__)
	#pragma clang loop unroll (enable)
	#elif __GNUC__ >= 8
	#pragma GCC unroll 10
	#endif
	for (i = 0; i < n; i++)
		printf("%d\n", i);
}

void disable(void)
{
	int i, n = 10;

	#if defined(__clang__)
	#pragma clang loop unroll (disable)
	#endif
	for (i = 0; i < n; i++)
		printf("%d\n", i);
}

int main(void)
{
	enable();
	disable();
	return 0;
}
