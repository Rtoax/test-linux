# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

TARGETS_NVCC := hello
TARGETS_NVCC += dim3
TARGETS_NVCC += parallel
TARGETS_NVCC += cudaMalloc
TARGETS_NVCC += cudaGetDeviceProperties
TARGETS_NVCC += matrix-mul

TARGETS := matrix-mul-c

CFLAGS_NVCC := -DHAVE_CUDA=1

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
cudaGetDeviceProperties: ${OUTPUT}cudaGetDeviceProperties.cu.o ${CUDA_HELPERS}
matrix-mul: ${OUTPUT}matrix-mul.cu.o ${CUDA_HELPERS}
matrix-mul-c: ${OUTPUT}matrix-mul.o
