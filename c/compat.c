#include <stdio.h>

#include "compat.h"

int foo_v1(int a, int b, int c, int d)
{
	return printf("4: %d %d %d %d\n", a, b, c, d);
}

#if !defined(__clang__)
DEFAULT_VERSION(prog_load_v0_6_0, prog_load, LIB0.6.0)
#endif
int foo_v2(int a, int b, int c, int d, int e, int f)
{
	return printf("6: %d %d %d %d %d %d\n", a, b, c, d, e, f);
}

int main(void)
{
	foo(1, 2, 3, 4, 5, 6);
	foo(1, 2, 3, 4);

	return 0;
}
