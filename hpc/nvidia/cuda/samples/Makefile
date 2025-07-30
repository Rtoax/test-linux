# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

targets-nvcc := hello
targets-nvcc += dim3
targets-nvcc += parallel
targets-nvcc += cudaMalloc
targets-nvcc += cudaGetDeviceProperties
targets-nvcc += cudaDeviceGetP2PAttribute
targets-nvcc += cudaDeviceGetAttribute
targets-nvcc += cudaEvent
targets-nvcc += matrix matrix-double matrix-int8
targets-nvcc += blas blas-double
targets-nvcc += rand

targets-post := $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))

targets := matrix-c
targets += matrix-c-double

CFLAGS_NVCC := -DHAVE_CUDA=1

CFLAGS_matrix-double := -DTEST_DOUBLE=1
CFLAGS_NVCC_matrix-double := -DTEST_DOUBLE=1
CFLAGS_NVCC_matrix-int8 := -DTEST_INT8=1
LDFLAGS_NVCC_blas := -lcublas
CFLAGS_NVCC_blas-double := -DTEST_DOUBLE=1
LDFLAGS_NVCC_blas-double := -lcublas
LDFLAGS_NVCC_rand := -lcurand

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
blas: ${OUTPUT}blas.cu.o ${CUDA_HELPERS}
blas-double: ${OUTPUT}blas-double.cu.o ${CUDA_HELPERS}
rand: ${OUTPUT}rand.cu.o ${CUDA_HELPERS}
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
cudaGetDeviceProperties: ${OUTPUT}cudaGetDeviceProperties.cu.o ${CUDA_HELPERS}
cudaDeviceGetP2PAttribute: ${OUTPUT}cudaDeviceGetP2PAttribute.cu.o ${CUDA_HELPERS}
cudaDeviceGetAttribute: ${OUTPUT}cudaDeviceGetAttribute.cu.o ${CUDA_HELPERS}
cudaEvent: ${OUTPUT}cudaEvent.cu.o ${CUDA_HELPERS}
matrix: ${OUTPUT}matrix.cu.o ${CUDA_HELPERS}
matrix-double: ${OUTPUT}matrix-double.cu.o ${CUDA_HELPERS}
matrix-int8: ${OUTPUT}matrix-int8.cu.o ${CUDA_HELPERS}
matrix-c: ${OUTPUT}matrix.o
matrix-c-double: ${OUTPUT}matrix-double.o
