# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
OUTPUT := .output/

include nvidia/cuda.mk
include cestc/luca.mk

common-objs := activity
common-objs += subscribe
common-objs += version

# FIXME: only cuda support right now
cuda-objs := sampling
cuda-objs += range

target-nvcc-${HAVE_CUPTI} := ${common-objs}
target-nvcc-${HAVE_CUPTI} += ${cuda-objs}
target-lscc-${HAVE_LCPTI} := $(patsubst %,%-luca,$(common-objs))

include main.mk

# $1: obj name
define pti_obj
${1}-luca: ${OUTPUT}${1}.luca.o
endef

$(foreach obj, ${common-objs}, $(eval $(call pti_obj,${obj})))
