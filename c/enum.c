#include <stdio.h>
#include <inttypes.h>

#if defined(M32)
# define PRI	PRId32
#else
# define PRI	PRId64
#endif

enum {
	a = 1,
	b = 2,
};

enum {
	A = 1L,
	B = 2L,
};

enum {
	AL = 1L,
	BL = 2L,
#if !defined(M32)
	CL = 3L << 33,
#endif
};

int main(void)
{
	printf("%" PRI "\n", sizeof(a));
	printf("%" PRI "\n", sizeof(A)); /* 4 */
	printf("%" PRI "\n", sizeof(AL)); /* 8 */
	return 0;
}

