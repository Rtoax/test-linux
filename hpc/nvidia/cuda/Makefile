# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include cuda.mk

subdir-y := samples
subdir-y += fakeCUDA
subdir-y += intrinsics

target-shell-${HAVE_CUDA} := version.sh
target-nvcc-libso-${HAVE_CUDA} := libcuda_helper.so
target-nvcc-liba-${HAVE_CUDA} := libcuda_helper.a

include main.mk

libcuda_helper.so: $(OUTPUT)cuda_helpers.cu.so.o
libcuda_helper.a: $(OUTPUT)cuda_helpers.cu.a.o
