#include <stdio.h>

#define COUNT_NARG(...) COUNT_NARG_(__VA_ARGS__, COUNT_RSEQ_N())
#define COUNT_NARG_(...) COUNT_ARG_N(__VA_ARGS__)
#define COUNT_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define COUNT_RSEQ_N() 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

void count(void)
{
	printf("%d\n", COUNT_NARG(1));
	printf("%d\n", COUNT_NARG(x));
	printf("%d\n", COUNT_NARG(1, 2, 3));
	printf("%d\n", COUNT_NARG(1, 2, 3, 4, 5));
	printf("%d\n", COUNT_NARG(1, 2, 3, 4, 5, 6, 7));
	printf("%d\n", COUNT_NARG(1, 2, 3, 4, 5, 6, 7, 8, 9));
	printf("%d\n", COUNT_NARG(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
	printf("%d\n", COUNT_NARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10));
}

int main(void)
{
	count();
	return 0;
}
