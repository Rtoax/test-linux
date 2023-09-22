#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	float a = -23;
	float b = 12;
	float c = copysign(a, b);
	printf("%f\n", c);
	return 0;
}
