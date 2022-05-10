#include <stdio.h>

int my_clock_gettime()
{
	return printf("I am clock_gettime from custom vdso.\n");
}
