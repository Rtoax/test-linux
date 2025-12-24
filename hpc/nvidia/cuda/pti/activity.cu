#include "cuda_compat.h"
#include "cuda_helpers.h"

__global__ void kernel_1(void)
{
	printf("kernel\n");
}

static void BufferRequested(uint8_t **buffer, size_t *size, size_t *maxNumRecords)
{
}

static void BufferCompleted(CUcontext ctx, uint32_t streamId, uint8_t *buffer,
			    size_t size, size_t validSize)
{
}

int main(void)
{
	CUPTI_CHECK_EXIT(cuptiActivityRegisterCallbacks(BufferRequested, BufferCompleted));
	CUPTI_CHECK_EXIT(cuptiActivityEnable(CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL));

	kernel_1<<<1, 1>>>();

	cudaDeviceSynchronize();

	CUPTI_CHECK_EXIT(cuptiActivityFlushAll(1));
	CUPTI_CHECK_EXIT(cuptiActivityDisable(CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL));
	return 0;
}
