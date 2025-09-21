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

hiprtcResult hiprtcGetCode(hiprtcProgram prog, char* code)
{
	code[0] = 'F';
	return HIPRTC_SUCCESS;
}

hiprtcResult hiprtcGetCodeSize(hiprtcProgram prog, size_t* codeSizeRet)
{
	*codeSizeRet = 1024;
	return HIPRTC_SUCCESS;
}

hiprtcResult hiprtcGetBitcode(hiprtcProgram prog, char* bitcode)
{
	bitcode[0] = 'F';
	return HIPRTC_SUCCESS;
}

hiprtcResult hiprtcGetBitcodeSize(hiprtcProgram prog, size_t* bitcode_size)
{
	*bitcode_size = 1024;
	return HIPRTC_SUCCESS;
}

