# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

targets-nvcc := hello
targets-nvcc += dim3
targets-nvcc += cooperative
targets-nvcc += parallel
targets-nvcc += cudaMalloc
targets-nvcc += cudaMallocManaged
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

obj-cubin := hello.cubin
obj-fatbin := hello.fatbin

targets-post := $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.sass.dump,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-cubin))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-fatbin))

targets := matrix-c-fp32 matrix-c-fp64

CFLAGS_NVCC := -DHAVE_CUDA=1

CFLAGS_matrix-fp64 := -DTEST_FP64=1
CFLAGS_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_NVCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_NVCC_matrix-int8 := -DTEST_INT8=1

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
cooperative: ${OUTPUT}cooperative.cu.o ${CUDA_HELPERS}
blas: ${OUTPUT}blas.cu.o ${CUDA_HELPERS}
cublasLtMatmul: ${OUTPUT}cublasLtMatmul.cu.o ${CUDA_HELPERS}
rand: ${OUTPUT}rand.cu.o ${CUDA_HELPERS}
fft: ${OUTPUT}fft.cu.o ${CUDA_HELPERS}
sparse: ${OUTPUT}sparse.cu.o ${CUDA_HELPERS}
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
module: ${OUTPUT}module.cu.o ${CUDA_HELPERS}
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
cudaMallocManaged: ${OUTPUT}cudaMallocManaged.cu.o ${CUDA_HELPERS}
cudaGetDeviceProperties: ${OUTPUT}cudaGetDeviceProperties.cu.o ${CUDA_HELPERS}
cudaDeviceGetP2PAttribute: ${OUTPUT}cudaDeviceGetP2PAttribute.cu.o ${CUDA_HELPERS}
cudaDeviceGetAttribute: ${OUTPUT}cudaDeviceGetAttribute.cu.o ${CUDA_HELPERS}
cudaEvent: ${OUTPUT}cudaEvent.cu.o ${CUDA_HELPERS}
matrix-fp16: ${OUTPUT}matrix-fp16.cu.o ${CUDA_HELPERS}
matrix-fp32: ${OUTPUT}matrix-fp32.cu.o ${CUDA_HELPERS}
matrix-fp64: ${OUTPUT}matrix-fp64.cu.o ${CUDA_HELPERS}
matrix-int8: ${OUTPUT}matrix-int8.cu.o ${CUDA_HELPERS}
matrix-c-fp32: ${OUTPUT}matrix-fp32.o
matrix-c-fp64: ${OUTPUT}matrix-fp64.o
__GNUC__: ${OUTPUT}__GNUC__.cu.o
__STDC__: ${OUTPUT}__STDC__.cu.o
