#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>

#if defined(M32)
# define PRI	PRId32
#else
# define PRI	PRId64
#endif

int main(void)
{
	size_t sz = 16;
	int n = -1;

#define PRINT()	\
	printf("%d %s %" PRI "\n", n, n < sz ? "<" : ">=", sz);	\
	printf("%d %s %" PRI "\n", n, n < (int)sz ? "<" : ">=", sz);

	PRINT();

	n = 1;

	PRINT();

	return 0;
}
