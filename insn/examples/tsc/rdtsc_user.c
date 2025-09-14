#include <stdio.h>
#include "rdtsc.h"

int main(void)
{
	uint64_t tsc = rdtsc();

	printf("tsc = %ld\n", tsc);

	return 0;
}

