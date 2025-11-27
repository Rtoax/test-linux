# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include cuda.mk
include rocm.mk
include hpcc.mk
include luca.mk

subdir-y := samples
subdir-y += fft
subdir-y += intrinsics
subdir-y += fakeCUDA

target-shell-${HAVE_CUDA} := version.sh
target-nvcc-libso-${HAVE_CUDA} := libcuda_helper.so
target-nvcc-liba-${HAVE_CUDA} := libcuda_helper.a
target-hipcc-libso-${HAVE_HIP} := libhip_helper.so
target-hipcc-liba-${HAVE_HIP} := libhip_helper.a
target-htcc-libso-${HAVE_HPCC} := libhpcc_helper.so
target-htcc-liba-${HAVE_HPCC} := libhpcc_helper.a
target-lscc-libso-${HAVE_LUCA} := libluca_helper.so
target-lscc-liba-${HAVE_LUCA} := libluca_helper.a

include main.mk

libcuda_helper.so: $(OUTPUT)cuda_helpers.cu.so.o
libcuda_helper.a: $(OUTPUT)cuda_helpers.cu.a.o
libhip_helper.so: $(OUTPUT)cuda_helpers.hip.so.o
libhip_helper.a: $(OUTPUT)cuda_helpers.hip.a.o
libhpcc_helper.so: $(OUTPUT)cuda_helpers.hpcc.so.o
libhpcc_helper.a: $(OUTPUT)cuda_helpers.hpcc.a.o
libluca_helper.so: $(OUTPUT)cuda_helpers.luca.so.o
libluca_helper.a: $(OUTPUT)cuda_helpers.luca.a.o
