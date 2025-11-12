#include <stdio.h>
#include "cuda_compat.h"


int main(void)
{
	ncclResult_t result;
	int version = 0;

	result = ncclGetVersion(&version);
	printf("version %d, %s\n", version, ncclGetErrorString(result));

	return 0;
}
