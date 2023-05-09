#include <stdio.h>
#include "rdtsc.h"

int main(void)
{
	uint64_t tscp = rdtscp();

	printf("tscp = %ld\n", tscp);

	return 0;
}

