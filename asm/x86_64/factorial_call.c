#include <stdio.h>
#include <inttypes.h>

uint64_t factorial(uint64_t n);

int main(void)
{
	uint64_t i;
	for (i = 0; i < 20; i++) {
		printf("factorial(%2lu) = %lu\n", i, factorial(i));
	}
	return 0;
}

