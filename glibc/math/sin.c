#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	float fcosy, fsiny;
	double x, cosy, siny;
	long double cosx, sinx;

	x = M_PI / 3;

	printf("cos(%lf) = %f\n", x, cos(x));
	printf("cosf(%lf) = %f\n", x, cosf(x));
	printf("cosl(%Lf) = %Lf\n", (long double)x, cosl(x));

	printf("sin(%lf) = %f\n", x, sin(x));
	printf("sinf(%lf) = %f\n", x, sinf(x));
	printf("sinl(%Lf) = %Lf\n", (long double)x, sinl(x));

	printf("tan(%lf) = %f\n", x, tan(x));
	printf("tanf(%lf) = %f\n", x, tanf(x));
	printf("tanl(%Lf) = %Lf\n", (long double)x, tanl(x));

	sincos(x, &siny, &cosy);
	printf("sin(%f) = %lf, cos(%f) = %lf\n", x, siny, x, cosy);
	sincosf(x, &fsiny, &fcosy);
	sincosl(x, &sinx, &cosx);

	return 0;
}
