#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	double v, x;

	x = M_E;

#if defined(STRESS)
	while (1)
#endif
		v = log(x);

	printf("log(%lf) = %lf\n", x, v);
	return 0;
}
