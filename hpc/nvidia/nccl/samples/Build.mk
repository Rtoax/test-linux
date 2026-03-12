# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include nvidia/cuda.mk
include nvidia/nccl.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk

common-objs := version
common-objs += communicator

# NVIDIA CUDA
target-nvcc-${HAVE_NCCL} := ${common-objs}
target-hipcc-${HAVE_RCCL} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))
