#include <stdio.h>
#include <math.h>

int main(void)
{
	float a = nan("NAN");
	printf("a = %f\n", a);
	return 0;
}
