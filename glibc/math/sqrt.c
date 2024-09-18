#include <stdio.h>
#include <math.h>

int main(void)
{
	double v, d;

	v = 16.0;

#if defined(STRESS)
	/**
	 * Test with: $ sudo perf top -p $(pidof sqrt-stress)
	 *
	 * Note: if sqrt(16.0) directly, sqrt will be optimized out.
	 */
	while (1)
#endif
		d = sqrt(v);

	printf("%lf\n", d);
	return 0;
}
