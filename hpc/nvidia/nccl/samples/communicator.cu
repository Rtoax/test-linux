#include <stdio.h>
#include <malloc.h>
#include "cuda_compat.h"


int main(int argc, char *argv[])
{
	int i, ngpu, *devs;
	size_t datasz;
	ncclComm_t *comms;
	float **sendbuff, **recvbuff;
	cudaStream_t *streams;

	datasz = 32 * 1024 * 1024;

	cudaGetDeviceCount(&ngpu);

	sendbuff = (float **)malloc(ngpu * sizeof(float *));
	recvbuff = (float **)malloc(ngpu * sizeof(float *));
	streams = (cudaStream_t *)malloc(ngpu * sizeof(cudaStream_t));

	for (i = 0; i < ngpu; i++) {
		cudaSetDevice(i);
		cudaMalloc((void **)sendbuff + i, datasz * sizeof(float));
		cudaMalloc((void **)recvbuff + i, datasz * sizeof(float));
		cudaMemset(sendbuff[i], 1, datasz * sizeof(float));
		cudaMemset(recvbuff[i], 0, datasz * sizeof(float));
		cudaStreamCreate(streams + i);
	}

	comms = (ncclComm_t *)malloc(sizeof(ncclComm_t) * ngpu);
	devs = (int *)malloc(sizeof(int) * ngpu);
	for (i = 0; i < ngpu; i++) {
		devs[i] = i;
	}

	ncclCommInitAll(comms, ngpu, devs);

	ncclGroupStart();

	// TODO

	ncclGroupEnd();

	for (i = 0; i < ngpu; i++) {
		cudaSetDevice(i);
		cudaStreamSynchronize(streams[i]);
	}

	for (i = 0; i < ngpu; i++) {
		cudaSetDevice(i);
		cudaFree(sendbuff[i]);
		cudaFree(recvbuff[i]);
	}
	for (i = 0; i < ngpu; i++) {
		ncclCommDestroy(comms[i]);
	}
	free(comms);
	return 0;
}
