#include <stdio.h>
#include <math.h>

int main(void)
{
	float a = nan("NAN");
	printf("a = %f, %d\n", a, isnan(a));
	return 0;
}
