#include <math.h>
#include <stdio.h>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078

void base(void)
{
	double f64 = PI;
	printf("%.64f\n", (double)f64);
}

int main(void)
{
	base();
	return 0;
}
