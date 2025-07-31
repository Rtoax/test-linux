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
targets-nvcc += cublasLtMatmul
targets-nvcc += matrix matrix-double matrix-int8
targets-nvcc += blas
targets-nvcc += rand
targets-nvcc += __GNUC__ __STDC__

targets-post := $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))

targets := matrix-c
targets += matrix-c-double

CFLAGS_NVCC := -DHAVE_CUDA=1

CFLAGS_matrix-double := -DTEST_DOUBLE=1
CFLAGS_NVCC_matrix-double := -DTEST_DOUBLE=1
CFLAGS_NVCC_matrix-int8 := -DTEST_INT8=1
LDFLAGS_NVCC_blas := -lcublas
LDFLAGS_NVCC_cublasLtMatmul := -lcublas -lcublasLt
LDFLAGS_NVCC_rand := -lcurand

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
blas: ${OUTPUT}blas.cu.o ${CUDA_HELPERS}
cublasLtMatmul: ${OUTPUT}cublasLtMatmul.cu.o ${CUDA_HELPERS}
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
__GNUC__: ${OUTPUT}__GNUC__.cu.o
__STDC__: ${OUTPUT}__STDC__.cu.o
