# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

subdir-y := samples
subdir-y += fakeCUDA
subdir-y += intrinsics

target-nvcc-libso-y := libcuda_helper.so
target-nvcc-liba-y := libcuda_helper.a

include ../../../template/main.mk

libcuda_helper.so: $(OUTPUT)cuda_helpers.cu.so.o
libcuda_helper.a: $(OUTPUT)cuda_helpers.cu.a.o
