# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

targets-nvcc := hello
targets-nvcc += dim3
targets-nvcc += parallel
targets-nvcc += cudaMalloc
targets-nvcc += cudaGetDeviceProperties
targets-nvcc += cudaDeviceGetP2PAttribute
targets-nvcc += matrix-mul matrix-mul-double matrix-mul-int8
targets-nvcc += blas blas-double

targets-post := $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))

targets := matrix-mul-c
targets += matrix-mul-c-double

CFLAGS_NVCC := -DHAVE_CUDA=1

CFLAGS_matrix-mul-double := -DTEST_DOUBLE=1
CFLAGS_NVCC_matrix-mul-double := -DTEST_DOUBLE=1
CFLAGS_NVCC_matrix-mul-int8 := -DTEST_INT8=1
LDFLAGS_NVCC_blas := -lcublas
CFLAGS_NVCC_blas-double := -DTEST_DOUBLE=1
LDFLAGS_NVCC_blas-double := -lcublas

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
blas: ${OUTPUT}blas.cu.o ${CUDA_HELPERS}
blas-double: ${OUTPUT}blas-double.cu.o ${CUDA_HELPERS}
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
cudaGetDeviceProperties: ${OUTPUT}cudaGetDeviceProperties.cu.o ${CUDA_HELPERS}
cudaDeviceGetP2PAttribute: ${OUTPUT}cudaDeviceGetP2PAttribute.cu.o ${CUDA_HELPERS}
matrix-mul: ${OUTPUT}matrix-mul.cu.o ${CUDA_HELPERS}
matrix-mul-double: ${OUTPUT}matrix-mul-double.cu.o ${CUDA_HELPERS}
matrix-mul-int8: ${OUTPUT}matrix-mul-int8.cu.o ${CUDA_HELPERS}
matrix-mul-c: ${OUTPUT}matrix-mul.o
matrix-mul-c-double: ${OUTPUT}matrix-mul-double.o
