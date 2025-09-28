#include <stdio.h>

#define TRACE()	do { \
		printf("%s:%d\n", __func__, __LINE__); \
	} while (0)

#define __fc_global__	__attribute__((fakecuda_global))
#define __fc_device__	__attribute__((fakecuda_device))
#define __fc_device_builtin__	__attribute__((fakecuda_device_builtin))

struct st1 {
	int a;
};

struct __fc_device_builtin__ uint3
{
	unsigned int x, y, z;
};

typedef __fc_device_builtin__ struct uint3 uint3;

uint3 __attribute__((device_builtin)) extern const threadIdx;

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
