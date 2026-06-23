#include <stdio.h>
#include <math.h>

int main(void)
{
	float a = -12;
	int b = signbit(a);

	printf("a = %f, b = %d\n", a, b ? -1 : 1);

	a = 12;
	b = signbit(a);
	printf("%f: %d\n", a, b ? -1 : 1);

	return 0;
}
