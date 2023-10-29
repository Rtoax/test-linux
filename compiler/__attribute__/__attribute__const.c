#include <stdio.h>

#define __const __attribute__((const))

int square(int a) __const;
int square(int a)
{
	return a * a;
}

int main(void)
{
	printf("----------%d\n", square(5));
	printf("----------%d\n", square(5));
	printf("----------%d\n", square(2));
	return 0;
}
