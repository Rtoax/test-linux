# SPDX-License-Identifier: GPL-3.0
TARGETS_NVCC := hello
TARGETS_NVCC += parallel
TARGETS_NVCC += cudaMalloc

CFLAGS_NVCC := -Wno-deprecated-gpu-targets
LDFLAGS_NVCC := -Wno-deprecated-gpu-targets

include ../../../../template/main.mk

cuda_helpers.cu.o: cuda_helpers.h

hello: hello.cu.o
parallel: parallel.cu.o
cudaMalloc: cudaMalloc.cu.o cuda_helpers.cu.o
