# SPDX-License-Identifier: GPL-3.0
include nvidia/cuda.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk
include compiler.mk
include helpers.mk

common-objs := sparse

target-nvcc-${HAVE_CUDA} := ${common-objs}
target-hipcc-${HAVE_HIP} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))
