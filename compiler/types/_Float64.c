#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846264338327950288419716939937510

void base(void)
{
	_Float64 f64 = (_Float64)PI;
	printf("%.17f\n", (double)f64);
}

int main(void)
{
	base();
	return 0;
}
