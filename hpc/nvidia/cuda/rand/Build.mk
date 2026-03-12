# SPDX-License-Identifier: GPL-3.0
__IGNORE_NOTFOUND_ERROR__ := 1

include nvidia/cuda.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk
include compiler.mk

__USE_CUDA_HELPERS__ = ${HAVE_CUDA}
__USE_HIP_HELPERS__ = ${HAVE_HIP}
__USE_LUCA_HELPERS__ = ${HAVE_LUCA}
__USE_HPCC_HELPERS__ = ${HAVE_HPCC}

common-objs := rand

target-nvcc-${HAVE_CUDA} := ${common-objs}
target-hipcc-${HAVE_HIP} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))
