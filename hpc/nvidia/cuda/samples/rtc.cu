// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
/**
 * RTC - RunTime Compilation
 *
 * CUDA: PTX
 * LUCA: Bitcode
 */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const char prog_buffer[] = { " \
	extern \"C\" __global__ void kernelHello(void) { \
		printf(\"Hello from GPU.\\n\"); \
	}" };

const char *compile_opts[] = { "-arch=sm_86" };

#if defined(__NVCC__)
void launch_from_ptx(nvrtcProgram prog)
{
	size_t ptx_size;
	char *ptx = NULL;

	NVRTC_CHECK_EXIT(nvrtcGetPTXSize(prog, &ptx_size));
	if (ptx_size <= 1) {
		fprintf(stderr, "ERROR: Get PTX failed\n");
		return;
	}

	ptx = (char *)malloc(ptx_size);
	NVRTC_CHECK_EXIT(nvrtcGetPTX(prog, ptx));
	printf("PTX size %ld, PTX:\n%s\n", ptx_size, ptx);

	CUdevice device;
	CHECK_CUDA_ERROR_EXIT(cuDeviceGet(&device, 0));

	CUcontext ctx;
	CHECK_CUDA_ERROR_EXIT(cuCtxCreate(&ctx, NULL, 0, device));

	CUmodule module;
	CHECK_CUDA_ERROR_EXIT(cuModuleLoadData(&module, ptx));
	free(ptx);

	CUfunction kernel;
	CHECK_CUDA_ERROR_EXIT(
		cuModuleGetFunction(&kernel, module, "kernelHello"));

	CHECK_CUDA_ERROR_EXIT(
		cuLaunchKernel(kernel, 1, 1, 1, 1, 1, 1, 0, NULL, NULL, NULL));

	CHECK_CUDA_ERROR_EXIT(cuCtxSynchronize());

	CHECK_CUDA_ERROR_EXIT(cuModuleUnload(module));
	CHECK_CUDA_ERROR_EXIT(cuCtxDestroy(ctx));
}
#define launch_prog launch_from_ptx
#elif defined(__LUCA__) || defined(__HIPCC__)
void launch_from_bitcode(nvrtcProgram prog)
{
	size_t bc_size;
	char *bc;

	NVRTC_CHECK_EXIT(hiprtcGetBitcodeSize(prog, &bc_size));
	if (bc_size <= 1) {
		fprintf(stderr, "ERROR: Get bitcode failed\n");
		return;
	}

	bc = (char *)malloc(bc_size);
	NVRTC_CHECK_EXIT(hiprtcGetBitcode(prog, bc));
	printf("Bitcode size %ld, bitcode:\n%s\n", bc_size, bc);

	/* TODO: finish me */
}
#define launch_prog launch_from_bitcode
#else
#error "You are not one of NVCC/LUCA/HIP, develope me"
#endif

int main(void)
{
	nvrtcProgram prog;
	nvrtcResult ret;
	size_t log_size;

	NVRTC_CHECK_EXIT(
		nvrtcCreateProgram(&prog, prog_buffer, "hello", 0, NULL, NULL));

	ret = nvrtcCompileProgram(prog, ARRAY_SIZE(compile_opts), compile_opts);
	NVRTC_CHECK_EXIT(nvrtcGetProgramLogSize(prog, &log_size));
	if (log_size > 1) {
		char *log = (char *)malloc(log_size);
		NVRTC_CHECK_EXIT(nvrtcGetProgramLog(prog, log));
		printf("Compile log:\n%s\n", log);
		free(log);
	}

	if (ret != NVRTC_SUCCESS) {
		fprintf(stderr, "ERROR: CompileProgram failed, %s\n",
			nvrtcGetErrorString(ret));
		exit(EXIT_FAILURE);
	}

	launch_prog(prog);

	NVRTC_CHECK_EXIT(nvrtcDestroyProgram(&prog));

	return 0;
}
