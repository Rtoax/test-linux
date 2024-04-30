#include <stdio.h>
#include <math.h>

int main(void)
{
	float x = 13, y = -9;
	float a;

	a = nextafter(x, y);
	printf("nextafter %f\n", a);

	a = nexttoward(x, y);
	printf("nexttoward %f\n", a);

	return 0;
}
