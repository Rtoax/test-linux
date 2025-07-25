# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

targets-nvcc := hello
targets-nvcc += dim3
targets-nvcc += parallel
targets-nvcc += cudaMalloc
targets-nvcc += cudaGetDeviceProperties
targets-nvcc += cudaDeviceGetP2PAttribute
targets-nvcc += matrix-mul

targets := matrix-mul-c

CFLAGS_NVCC := -DHAVE_CUDA=1

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
cudaGetDeviceProperties: ${OUTPUT}cudaGetDeviceProperties.cu.o ${CUDA_HELPERS}
cudaDeviceGetP2PAttribute: ${OUTPUT}cudaDeviceGetP2PAttribute.cu.o ${CUDA_HELPERS}
matrix-mul: ${OUTPUT}matrix-mul.cu.o ${CUDA_HELPERS}
matrix-mul-c: ${OUTPUT}matrix-mul.o
