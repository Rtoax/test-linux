#include <stdio.h>
#include <string.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

__global__ void checkIndex(void)
{
	int ix = threadIdx.x + blockDim.x * blockIdx.x;
	int iy = threadIdx.y + blockDim.y * blockIdx.y;
	int iz = threadIdx.z + blockDim.z * blockIdx.z;

	printf("threadIdx(%d,%d,%d), blockIdx(%d,%d,%d), blockDim(%d,%d,%d), gridDim(%d,%d,%d) (%d,%d,%d)\n",
		threadIdx.x, threadIdx.y, threadIdx.z,
		blockDim.x, blockDim.y, blockDim.z,
		blockIdx.x, blockIdx.y, blockIdx.z,
		gridDim.x, gridDim.y, gridDim.z,
		ix, iy, iz);
/**
 * FIXME: MetaX htcc have wrong threadIdx.x, add printf could fix it.
 */
#if defined(HAVE_HCCL)
	printf("");
#endif
}

int main(int argc, char *argv[])
{
	int i, bx, by, bz, gx, gy, gz;

	bx = gx = 3;
	by = gy = 1;
	bz = gz = 1;

	for (i = 1; i < argc; i++) {
#define xyz(v) if (!strncmp(#v"=", argv[i], 3)) v = atoi(argv[i] + 3);
		xyz(bx);
		xyz(by);
		xyz(bz);
		xyz(gx);
		xyz(gy);
		xyz(gz);
#undef xyz
	}

	fprintf(stderr, "Usage: %s [bx|by|bz|gx|gy|gz=<N>]\n", argv[0]);
	fprintf(stderr, "<<< grid(%d,%d,%d), block(%d,%d,%d) >>>\n",
		gx, gy, gz, bx, by, bz);

	dim3 block(bx, by, bz);
	dim3 grid(gx, gy, gz);

	gpu_init(0);

	checkIndex<<<grid, block>>>();

	/* flush printf */
	cudaDeviceSynchronize();

	return 0;
}
