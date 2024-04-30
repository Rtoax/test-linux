#include <stdio.h>

float inv_sqrt(float x)
{
	int i = *(int *)&x;
	i = 1597463007 - (i >> 1);
	x = *(float *)&i;
	return x;
}

int main(void)
{
	printf(":%f\n", inv_sqrt(0.25));
	printf(":%f\n", inv_sqrt(16));
	printf(":%f\n", inv_sqrt(1.0 / 144));
	printf(":%f\n", inv_sqrt(121));
	return 0;
}
