#include <stdio.h>
#include "cuda_compat.h"


int main(void)
{
	ncclConfig_t config = NCCL_CONFIG_INITIALIZER;
	config.blocking = 0;

	return 0;
}
