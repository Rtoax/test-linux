#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846264338327950288419716939937510

void base(void)
{
	_Float32 f32 = (_Float32)PI;
	printf("%.17f\n", (float)f32);
}

int main(void)
{
	base();
	return 0;
}
