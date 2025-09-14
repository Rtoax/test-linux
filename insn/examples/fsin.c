#include <stdio.h>

#define PI	3.1415926

int main(void)
{
	float answer;
	float angle = (PI/2);
	asm ("fsin" : "=t"(answer) : "0" (angle));
	printf("fsin(%f) = %f\n", angle, answer);
	return 0;
}
