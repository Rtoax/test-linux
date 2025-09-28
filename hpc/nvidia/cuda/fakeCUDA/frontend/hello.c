#include <stdio.h>

#define TRACE()	do { \
		printf("%s:%d\n", __func__, __LINE__); \
	} while (0)

#define __fc_global__	__attribute__((fakecuda_global))
#define __fc_device__	__attribute__((fakecuda_device))

struct st1 {
	int a;
};

__fc_device__ int a = 0;
__fc_device__ struct st1 st1;

__fc_device__ void kernel_device(void)
{
	TRACE();
}

__fc_global__ void kernel1(void)
{
	TRACE();
	kernel_device();
}

int main(void)
{
	TRACE();
	kernel1();
	return 0;
}
