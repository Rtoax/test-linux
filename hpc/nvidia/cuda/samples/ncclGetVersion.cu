#include <stdio.h>
#include "cuda_compat.h"


int main(void)
{
	int version = 0;
	hcclGetVersion(&version);
	printf("version %d\n", version);
	return 0;
}
