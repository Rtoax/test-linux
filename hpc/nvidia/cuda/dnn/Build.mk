# SPDX-License-Identifier: GPL-3.0
__IGNORE_NOTFOUND_ERROR__ := 1

include nvidia/cuda.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk

__USE_CUDA_HELPERS__ = ${HAVE_CUDNN}
__USE_HIP_HELPERS__ = ${HAVE_HIPDNN}
__USE_LUCA_HELPERS__ = ${HAVE_LCDNN}
__USE_HPCC_HELPERS__ = ${HAVE_HCDNN}

common-objs := version

target-nvcc-${HAVE_CUDNN} := ${common-objs}
target-hipcc-${HAVE_HIPDNN} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HCDNN} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LCDNN} := $(patsubst %,%-luca,$(common-objs))
