#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(void)
{
	int count;
	cudaGetDeviceCount(&count);
	printf("count %d\n", count);
	return 0;
}
