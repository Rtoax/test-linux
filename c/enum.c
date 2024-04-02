#include <stdio.h>

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
	CL = 3L << 33,
};

int main(void)
{
	printf("%ld\n", sizeof(a));
	printf("%ld\n", sizeof(A)); /* 4 */
	printf("%ld\n", sizeof(AL)); /* 8 */
	return 0;
}

