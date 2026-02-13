#include <stdio.h>
#include <malloc.h>
#include <nccl.h>
#include <cuda_runtime.h>
#include "../nccl_helpers.h"

int main(int argc, char *argv[])
{
	int i, ngpu, *devs;
	size_t datasz;
	ncclComm_t *comms;
	float **sendbuff, **recvbuff, **cpu_recvbuff;
	cudaStream_t *streams;

	datasz = 32 * 1024 * 1024;

	cudaGetDeviceCount(&ngpu);

	sendbuff = (float **)malloc(ngpu * sizeof(float *));
	recvbuff = (float **)malloc(ngpu * sizeof(float *));
	cpu_recvbuff = (float **)malloc(ngpu * sizeof(float *));
	streams = (cudaStream_t *)malloc(ngpu * sizeof(cudaStream_t));

	for (i = 0; i < ngpu; i++) {
		cudaSetDevice(i);

		cudaMalloc((void **)sendbuff + i, datasz * sizeof(float));
		cudaMalloc((void **)recvbuff + i, datasz * sizeof(float));

		cudaMemset(sendbuff[i], 1, datasz * sizeof(float));
		cudaMemset(recvbuff[i], 0, datasz * sizeof(float));

		cudaStreamCreate(streams + i);

		cpu_recvbuff[i] = (float *)malloc(datasz * sizeof(float));
		memset(cpu_recvbuff[i], 0, datasz * sizeof(float));
	}

	comms = (ncclComm_t *)malloc(sizeof(ncclComm_t) * ngpu);
	devs = (int *)malloc(sizeof(int) * ngpu);
	for (i = 0; i < ngpu; i++) {
		devs[i] = i;
	}

	NCCL_CHECK_EXIT(ncclCommInitAll(comms, ngpu, devs));

	NCCL_CHECK_EXIT(ncclGroupStart());

	for (i = 0; i < ngpu; i++) {
		NCCL_CHECK_EXIT(ncclAllReduce((const void*)sendbuff[i],
				(void*)recvbuff[i],
				datasz, ncclFloat, ncclSum,
				comms[i], streams[i]));
	}

	NCCL_CHECK_EXIT(ncclGroupEnd());

	for (i = 0; i < ngpu; i++) {
		cudaSetDevice(i);
		cudaStreamSynchronize(streams[i]);
	}

	/* Check the recvbuff of AllReduce */
	for (i = 0; i < ngpu; i++) {
		cudaMemcpy(cpu_recvbuff[i], recvbuff[i], datasz,
			cudaMemcpyDeviceToHost);
		/* FIXME: luca: print 0.00 ??? */
		printf("GPU %d Recv %.2f\n", i, cpu_recvbuff[i][0]);
	}

	for (i = 0; i < ngpu; i++) {
		cudaSetDevice(i);
		cudaFree(sendbuff[i]);
		cudaFree(recvbuff[i]);
		free(cpu_recvbuff[i]);
	}

	free(sendbuff);
	free(recvbuff);
	free(cpu_recvbuff);

	for (i = 0; i < ngpu; i++) {
		NCCL_CHECK_EXIT(ncclCommDestroy(comms[i]));
	}
	free(comms);
	return 0;
}
