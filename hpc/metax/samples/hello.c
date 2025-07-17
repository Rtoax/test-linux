#include <stdio.h>
#include <hc_runtime.h>

__host__ __device__ void func(void)
{
#ifdef __MACA_ARCH__
	/* Device code */
#else
	/* Host code */
#endif
}

int main(void)
{
	return 0;
}
