#define __USE_HIP__
#include "runtime.cpp"
#include "runtime-hip.hpp"


/**
 * FIXME: CUDA 12 don't has this API?
 */
int hipGetStreamDeviceId(hipStream_t stream)
{
	return 0;
}
