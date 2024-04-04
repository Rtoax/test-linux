#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

int show_complex(float complex c)
{
	printf("(%f, %f)\n", creal(c), cimag(c));
	return 0;
}

int main(void)
{
	float complex ic, icsin;

	ic = 12 + 23 * I;

	show_complex(ic);

	return 0;
}
