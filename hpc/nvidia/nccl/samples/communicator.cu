#include <stdio.h>
#include <malloc.h>
#include "cuda_compat.h"


int main(int argc, char *argv[])
{
	int i, ngpu, *devs;
	ncclConfig_t config = NCCL_CONFIG_INITIALIZER;
	ncclComm_t *comms;

	cudaGetDeviceCount(&ngpu);

	config.blocking = 0;

	comms = (ncclComm_t *)malloc(sizeof(ncclComm_t) * ngpu);
	devs = (int *)malloc(sizeof(int) * ngpu);
	for (i = 0; i < ngpu; i++)
		devs[i] = i;

	ncclCommInitAll(comms, ngpu, devs);

	for (i = 0; i < ngpu; i++)
		ncclCommDestroy(comms[i]);
	free(comms);
	return 0;
}
