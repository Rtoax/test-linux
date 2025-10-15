#include <stdio.h>

int GLOBAL_A = 0x55555555;
int GLOBAL_B = 0x88888888;
int GLOBAL_C = 0x33333333;

int main(void)
{
	printf("%x\n", *(unsigned int *)&GLOBAL_A);
	printf("%lx\n", *(unsigned long *)&GLOBAL_A);
	return 0;
}
