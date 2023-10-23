#include <stdio.h>
#include <inttypes.h>

unsigned int factorial(unsigned int n);

int main(void)
{
	unsigned int i;
	for (i = 0; i < 10; i++)
		printf("factorial(%2u) = %u\n", i, factorial(i));
	return 0;
}

