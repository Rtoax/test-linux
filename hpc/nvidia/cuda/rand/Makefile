# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include nvidia/cuda.mk
include gpu/rocm.mk
include gpu/luca.mk
include gpu/hpcc.mk
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

include main.mk

define rand_obj
${1}: ${OUTPUT}${1}.cu.o ${CUDA_HELPERS}
${1}-hip: ${OUTPUT}${1}.hip.o ${HIP_HELPERS}
${1}-hpcc: ${OUTPUT}${1}.hpcc.o ${HPCC_HELPERS}
${1}-luca: ${OUTPUT}${1}.luca.o ${LUCA_HELPERS}
endef

$(foreach obj, ${common-objs}, $(eval $(call rand_obj,${obj})))
