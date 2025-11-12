# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include ../../cuda/cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk
include ../../../cestc/luca.mk

common-objs := version

# NVIDIA CUDA
target-nvcc-${HAVE_NCCL} := ${common-objs}
target-hipcc-${HAVE_RCCL} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))

include ../../../../template/main.mk

version: ${OUTPUT}version.cu.o
version-hip: ${OUTPUT}version.hip.o
version-hpcc: ${OUTPUT}version.hpcc.o
version-luca: ${OUTPUT}version.luca.o
