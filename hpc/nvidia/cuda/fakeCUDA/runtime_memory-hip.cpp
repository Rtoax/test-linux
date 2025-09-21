#define __USE_HIP__
#include "runtime_memory.cpp"


hipError_t hipMemcpyWithStream(void* dst, const void* src, size_t sizeBytes,
                               hipMemcpyKind kind, hipStream_t stream)
{
	return hipSuccess;
}
