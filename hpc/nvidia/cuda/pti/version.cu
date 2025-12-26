#include <stdio.h>
#include <stdint.h>
#include "cuda_compat.h"

int main(void)
{
	uint32_t version = 0;
	cuptiGetVersion(&version);
	printf("CUPTI_API_VERSION = %d\n", CUPTI_API_VERSION);
	printf("cupti version %d\n", version);
	return 0;
}
