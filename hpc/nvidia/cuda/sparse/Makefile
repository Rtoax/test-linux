# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

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

common-objs := sparse

target-nvcc-${HAVE_CUDA} := ${common-objs}
target-hipcc-${HAVE_HIP} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))

define sparse_dep
${1}-hip-objs := ${OUTPUT}${1}.hip.o
endef

$(foreach obj, ${common-objs}, $(eval $(call sparse_dep,${obj})))

include main.mk

define sparse_obj
${1}-hpcc: ${OUTPUT}${1}.hpcc.o ${HPCC_HELPERS}
${1}-luca: ${OUTPUT}${1}.luca.o ${LUCA_HELPERS}
endef

$(foreach obj, ${common-objs}, $(eval $(call sparse_obj,${obj})))
