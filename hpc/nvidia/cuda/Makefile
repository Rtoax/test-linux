# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include cuda.mk
include rocm.mk

subdir-y := samples
subdir-y += fft
subdir-y += intrinsics
subdir-y += fakeCUDA

target-shell-${HAVE_CUDA} := version.sh
target-nvcc-libso-${HAVE_CUDA} := libcuda_helper.so
target-nvcc-liba-${HAVE_CUDA} := libcuda_helper.a
target-hipcc-libso-${HAVE_HIP} := libhip_helper.so
target-hipcc-liba-${HAVE_HIP} := libhip_helper.a

include main.mk

libcuda_helper.so: $(OUTPUT)cuda_helpers.cu.so.o
libcuda_helper.a: $(OUTPUT)cuda_helpers.cu.a.o
libhip_helper.so: $(OUTPUT)cuda_helpers.hip.so.o
libhip_helper.a: $(OUTPUT)cuda_helpers.hip.a.o
