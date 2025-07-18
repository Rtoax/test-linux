# SPDX-License-Identifier: GPL-3.0
TARGETS_NVCC := hello
TARGETS_NVCC += parallel

CFLAGS_NVCC := -Wno-deprecated-gpu-targets
LDFLAGS_NVCC := -Wno-deprecated-gpu-targets

include ../../../../template/main.mk

hello: hello.cu.o
parallel: parallel.cu.o
