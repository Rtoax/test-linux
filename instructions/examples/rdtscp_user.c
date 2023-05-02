#include <stdio.h>
#include "rdtsc.h"

int main(void)
{
	uint64_t tsc = rdtscp();

	printf("tsc = %ld\n", tsc);

	return 0;
}

