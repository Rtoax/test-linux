#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

int main(void)
{
	int complex ic, icsin;

	ic = 1 + 1 * I;

	icsin = ccos(ic);

	printf("%f, %f\n", cabsf(ic), cabsf(icsin));

	return 0;
}
