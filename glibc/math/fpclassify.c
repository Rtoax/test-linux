#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#define _print_(val) printf("%-32s : %d\n", #val, val)

int main(void)
{
	float f;
	int i, tt;

	for (i = -5; i < 5; i++) {
		f = 1.0 / i;
		tt = fpclassify(f);
		printf("fpclassify : %f %d\n", f, tt);
	}

	tt = fpclassify(INFINITY);
	printf("fpclassify : %f %d\n", INFINITY, tt);

	_print_(FP_NAN);
	_print_(FP_INFINITE);
	_print_(FP_ZERO);
	_print_(FP_SUBNORMAL);
	_print_(FP_NORMAL);

	return 0;
}

