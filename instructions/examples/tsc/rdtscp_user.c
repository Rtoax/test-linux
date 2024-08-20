#include <stdio.h>
#include "rdtsc.h"

int main(void)
{
	uint32_t rcx = 0;
	uint64_t tscp = rdtscp(&rcx);

	printf("tscp = %ld, %d\n", tscp, rcx);

	return 0;
}

