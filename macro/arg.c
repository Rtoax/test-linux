#include <stdio.h>

#define COUNT_ARGS(...) COUNT_ARGS_IMPL(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define COUNT_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N

void count(void)
{
	printf("%d\n", COUNT_ARGS(1));
	printf("%d\n", COUNT_ARGS(1, 2, 3));
	printf("%d\n", COUNT_ARGS(1, 2, 3, 4, 5));
	printf("%d\n", COUNT_ARGS(1, 2, 3, 4, 5, 6, 7));
	printf("%d\n", COUNT_ARGS(1, 2, 3, 4, 5, 6, 7, 8, 9));
}

int main(void)
{
	count();
	return 0;
}
