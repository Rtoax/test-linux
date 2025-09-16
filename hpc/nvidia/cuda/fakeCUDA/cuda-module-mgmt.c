#include <cuda.h>


CUresult cuModuleLoad(CUmodule* module, const char *fname)
{
	return CUDA_SUCCESS;
}

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char *name)
{
	return CUDA_SUCCESS;
}
