# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include ../../../../compiler/compiler.mk
include ../cuda.mk
include ../../../amd/rocm/rocm.mk

ifdef HAVE_CUDA
endif

ifdef HAVE_HIP
  rocm-hipcc := hello
  rocm-hipcc += blas
  rocm-hipcc += dim3
  rocm-hipcc += fft
  rocm-hipcc += sparse
  rocm-hipcc += rand
  rocm-hipcc += parallel
  rocm-hipcc += module
  rocm-hipcc += float
  rocm-hipcc += cooperative
  rocm-hipcc += matrix-fp32
  rocm-hipcc += hipEvent
  rocm-hipcc += hipMalloc
  rocm-hipcc += hipMallocManaged
  rocm-hipcc += hipblasLtMatmul
  rocm-hipcc += hipGetDeviceProperties
  rocm-hipcc += hipGetDeviceCount
  rocm-hipcc += hipDeviceGetP2PAttribute
  rocm-hipcc += __GNUC__

  rocm-fatbin := parallel.hip_fatbin parallel.hipFatBinSegment

  targets-hipcc := $(patsubst %,%-hip,$(rocm-hipcc))
endif

targets-nvcc := hello
targets-nvcc += dim3
targets-nvcc += cooperative
targets-nvcc += parallel
targets-nvcc += cudaMalloc
targets-nvcc += cudaMallocManaged
targets-nvcc += cudaGetDeviceCount
targets-nvcc += cudaGetDeviceProperties
targets-nvcc += cudaDeviceGetP2PAttribute
targets-nvcc += cudaDeviceGetAttribute
targets-nvcc += cudaEvent
targets-nvcc += cublasLtMatmul
targets-nvcc += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
targets-nvcc += blas
targets-nvcc += rand
targets-nvcc += fft
targets-nvcc += sparse
targets-nvcc += __GNUC__ __STDC__
targets-nvcc += module
targets-nvcc += float

obj-cubin := hello.cubin
obj-cubin += parallel.cubin
obj-fatbin := hello.fatbin
obj-fatbin += parallel.fatbin parallel.nv_fatbin parallel.nvFatBinSegment

targets-post := $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.cu.sass.dump,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.cu.ptx.dump,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.ptx,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-cubin))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-fatbin))
targets-post += $(patsubst %,${OUTPUT}%,$(rocm-fatbin))

targets := matrix-c-fp32 matrix-c-fp64
targets += float-c

CFLAGS_matrix-fp64 := -DTEST_FP64=1
CFLAGS_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_NVCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_NVCC_matrix-int8 := -DTEST_INT8=1
# NOTE: warning: ‘CUresult cuDeviceComputeCapability(int*, int*, CUdevice)’ is deprecated [-Wdeprecated-declarations]
CFLAGS_NVCC_cudaGetDeviceProperties := -Wno-deprecated-declarations

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o
HIP_HELPERS := ${OUTPUT}cuda_helpers.hip.o

CFLAGS_float-c := ${cflags-support-types}
LDFLAGS_float-c := -lm

# FIXME: on my fedora 42 env:
# fatal error: 'bits/c++config.h' file not found
CFLAGS_HIPCC := -I/usr/include/c++/15/x86_64-redhat-linux/
CFLAGS_HIPCC += -I.
CFLAGS_HIPCC += -Wno-unused-result

CFLAGS_HIPCC_matrix-fp32 := -DTEST_FP32=1

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h
${HIP_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
cooperative: ${OUTPUT}cooperative.cu.o ${CUDA_HELPERS}
blas: ${OUTPUT}blas.cu.o ${CUDA_HELPERS}
cublasLtMatmul: ${OUTPUT}cublasLtMatmul.cu.o ${CUDA_HELPERS}
rand: ${OUTPUT}rand.cu.o ${CUDA_HELPERS}
fft: ${OUTPUT}fft.cu.o ${CUDA_HELPERS}
sparse: ${OUTPUT}sparse.cu.o ${CUDA_HELPERS}
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
module: ${OUTPUT}module.cu.o ${CUDA_HELPERS}
float: ${OUTPUT}float.cu.o
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
cudaMallocManaged: ${OUTPUT}cudaMallocManaged.cu.o ${CUDA_HELPERS}
cudaGetDeviceProperties: ${OUTPUT}cudaGetDeviceProperties.cu.o ${CUDA_HELPERS}
cudaGetDeviceCount: ${OUTPUT}cudaGetDeviceCount.cu.o ${CUDA_HELPERS}
cudaDeviceGetP2PAttribute: ${OUTPUT}cudaDeviceGetP2PAttribute.cu.o ${CUDA_HELPERS}
cudaDeviceGetAttribute: ${OUTPUT}cudaDeviceGetAttribute.cu.o ${CUDA_HELPERS}
cudaEvent: ${OUTPUT}cudaEvent.cu.o ${CUDA_HELPERS}
matrix-fp16: ${OUTPUT}matrix-fp16.cu.o ${CUDA_HELPERS}
matrix-fp32: ${OUTPUT}matrix-fp32.cu.o ${CUDA_HELPERS}
matrix-fp64: ${OUTPUT}matrix-fp64.cu.o ${CUDA_HELPERS}
matrix-int8: ${OUTPUT}matrix-int8.cu.o ${CUDA_HELPERS}
matrix-c-fp32: ${OUTPUT}matrix-fp32.o
matrix-c-fp64: ${OUTPUT}matrix-fp64.o
float-c: ${OUTPUT}float-c.o
__GNUC__: ${OUTPUT}__GNUC__.cu.o
__STDC__: ${OUTPUT}__STDC__.cu.o

# ROCm HIP
${OUTPUT}hello.hip.o: hello.cu
hello-hip: ${OUTPUT}hello.hip.o ${HIP_HELPERS}
${OUTPUT}dim3.hip.o: dim3.cu
dim3-hip: ${OUTPUT}dim3.hip.o ${HIP_HELPERS}
__GNUC__-hip: ${OUTPUT}__GNUC__.hip.o ${HIP_HELPERS}
${OUTPUT}fft.hip.o: fft.cu
fft-hip: ${OUTPUT}fft.hip.o ${HIP_HELPERS}
${OUTPUT}blas.hip.o: blas.cu
blas-hip: ${OUTPUT}blas.hip.o ${HIP_HELPERS}
${OUTPUT}cooperative.hip.o: cooperative.cu
cooperative-hip: ${OUTPUT}cooperative.hip.o ${HIP_HELPERS}
${OUTPUT}float.hip.o: float.cu
float-hip: ${OUTPUT}float.hip.o ${HIP_HELPERS}
${OUTPUT}rand.hip.o: rand.cu
rand-hip: ${OUTPUT}rand.hip.o ${HIP_HELPERS}
${OUTPUT}sparse.hip.o: sparse.cu
sparse-hip: ${OUTPUT}sparse.hip.o ${HIP_HELPERS}
${OUTPUT}parallel.hip.o: parallel.cu
parallel-hip: ${OUTPUT}parallel.hip.o ${HIP_HELPERS}
${OUTPUT}module.hip.o: module.cu
module-hip: ${OUTPUT}module.hip.o ${HIP_HELPERS}
${OUTPUT}hipblasLtMatmul.hip.o: cublasLtMatmul.cu
hipblasLtMatmul-hip: ${OUTPUT}hipblasLtMatmul.hip.o ${HIP_HELPERS}
${OUTPUT}hipEvent.hip.o: cudaEvent.cu
hipEvent-hip: ${OUTPUT}hipEvent.hip.o ${HIP_HELPERS}
${OUTPUT}hipMalloc.hip.o: cudaMalloc.cu
hipMalloc-hip: ${OUTPUT}hipMalloc.hip.o ${HIP_HELPERS}
${OUTPUT}hipMallocManaged.hip.o: cudaMallocManaged.cu
hipMallocManaged-hip: ${OUTPUT}hipMallocManaged.hip.o ${HIP_HELPERS}
${OUTPUT}matrix-fp32.hip.o: matrix.cu
matrix-fp32-hip: ${OUTPUT}matrix-fp32.hip.o ${HIP_HELPERS}
${OUTPUT}hipGetDeviceProperties.hip.o: matrix.cu
hipGetDeviceProperties-hip: ${OUTPUT}hipGetDeviceProperties.hip.o ${HIP_HELPERS}
${OUTPUT}hipGetDeviceCount.hip.o: cudaGetDeviceCount.cu
hipGetDeviceCount-hip: ${OUTPUT}hipGetDeviceCount.hip.o ${HIP_HELPERS}
${OUTPUT}hipDeviceGetP2PAttribute.hip.o: cudaDeviceGetP2PAttribute.cu
hipDeviceGetP2PAttribute-hip: ${OUTPUT}hipDeviceGetP2PAttribute.hip.o ${HIP_HELPERS}
