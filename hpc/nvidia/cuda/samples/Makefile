# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

TARGETS_NVCC := hello
TARGETS_NVCC += parallel
TARGETS_NVCC += cudaMalloc

CFLAGS_NVCC := -Wno-deprecated-gpu-targets
LDFLAGS_NVCC := -Wno-deprecated-gpu-targets

include ../../../../template/main.mk

${OUTPUT}cuda_helpers.cu.o: cuda_helpers.h

hello: ${OUTPUT}hello.cu.o
parallel: ${OUTPUT}parallel.cu.o ${OUTPUT}cuda_helpers.cu.o
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${OUTPUT}cuda_helpers.cu.o
