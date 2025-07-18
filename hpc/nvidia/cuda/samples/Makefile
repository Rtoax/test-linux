# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

TARGETS_NVCC := hello
TARGETS_NVCC += parallel
TARGETS_NVCC += cudaMalloc
TARGETS_NVCC += matrix-mul

CFLAGS_NVCC := -DHAVE_CUDA=1
CFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC := -Wno-deprecated-gpu-targets

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h

hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
matrix-mul: ${OUTPUT}matrix-mul.cu.o ${CUDA_HELPERS}
