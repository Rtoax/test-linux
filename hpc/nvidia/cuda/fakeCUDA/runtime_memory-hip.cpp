#define __USE_HIP__
#include "runtime_memory.cpp"


hipError_t hipMemcpyWithStream(void* dst, const void* src, size_t sizeBytes,
                               hipMemcpyKind kind, hipStream_t stream)
{
	return hipSuccess;
}

hipError_t hipHostMalloc(void** ptr, size_t size, unsigned int flags)
{
	return hipSuccess;
}

hipError_t hipHostFree(void* ptr)
{
	return hipSuccess;
}

hipError_t hipExtMallocWithFlags(void** ptr, size_t sizeBytes, unsigned int flags)
{
	return hipSuccess;
}
