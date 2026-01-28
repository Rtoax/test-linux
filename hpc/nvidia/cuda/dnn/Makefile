# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include nvidia/cuda.mk
include amd/rocm.mk
include gpu/luca.mk
include gpu/hpcc.mk

__USE_CUDA_HELPERS__ = ${HAVE_CUDNN}
__USE_HIP_HELPERS__ = ${HAVE_HIPDNN}
__USE_LUCA_HELPERS__ = ${HAVE_LCDNN}
__USE_HPCC_HELPERS__ = ${HAVE_HCDNN}

common-objs := version

target-nvcc-${HAVE_CUDNN} := ${common-objs}
target-hipcc-${HAVE_HIPDNN} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HCDNN} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LCDNN} := $(patsubst %,%-luca,$(common-objs))

include main.mk

define dnn_obj
${1}: ${OUTPUT}${1}.cu.o ${CUDA_HELPERS}
${1}-hip: ${OUTPUT}${1}.hip.o ${HIP_HELPERS}
${1}-hpcc: ${OUTPUT}${1}.hpcc.o ${HPCC_HELPERS}
${1}-luca: ${OUTPUT}${1}.luca.o ${LUCA_HELPERS}
endef

$(foreach obj, ${common-objs}, $(eval $(call dnn_obj,${obj})))
