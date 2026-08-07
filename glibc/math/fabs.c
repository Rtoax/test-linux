#include <stdio.h>
#include <math.h>

int main(void)
{
#define FABS(v) printf("fabs(%s) = %f\n", #v, fabs(v));
#define FABSF(v) printf("fabsf(%s) = %lf\n", #v, fabsf(v));
#define FABSL(v) printf("fabsl(%s) = %Lf\n", #v, fabsl(v));
	FABS(3.14);
	FABS(-3.14);
	FABS(0);
	FABS(1 - 99);
	FABSF(0);
	FABSL(0);
	return 0;
}
