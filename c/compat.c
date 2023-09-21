#include <stdio.h>

#include "compat.h"

int prog_load_deprecated(int a, int b, int c, int d)
{
	return printf("4: %d %d %d %d\n", a, b, c, d);
}

DEFAULT_VERSION(prog_load_v0_6_0, prog_load, LIB0.6.0)
int prog_load(int a, int b, int c, int d, int e, int f)
{
	return printf("6: %d %d %d %d %d %d\n", a, b, c, d, e, f);
}

int main()
{
	prog_load(1, 2, 3, 4, 5, 6);
	prog_load(1, 2, 3, 4);
}
