# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ = y

include nvidia/cuda.mk
include amd/rocm.mk
include metax/hpcc.mk
include cestc/luca.mk

subdir-y := samples
subdir-y += blas
subdir-y += dnn
subdir-y += fft
subdir-y += file
subdir-y += pti
subdir-y += ptx
subdir-y += rand
subdir-y += sparse
subdir-y += solver
subdir-y += vpu
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

libcuda_helper.so-objs := $(OUTPUT)cuda_helpers.cu.so.o
libcuda_helper.a-objs := $(OUTPUT)cuda_helpers.cu.a.o
libhip_helper.so-objs := $(OUTPUT)cuda_helpers.hip.so.o
libhip_helper.a-objs := $(OUTPUT)cuda_helpers.hip.a.o

include main.mk

libhpcc_helper.so: $(OUTPUT)cuda_helpers.hpcc.so.o
libhpcc_helper.a: $(OUTPUT)cuda_helpers.hpcc.a.o
libluca_helper.so: $(OUTPUT)cuda_helpers.luca.so.o
libluca_helper.a: $(OUTPUT)cuda_helpers.luca.a.o
