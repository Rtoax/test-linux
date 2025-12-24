# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
OUTPUT := .output/

include cuda.mk
include luca.mk

common-objs := subscribe

target-nvcc-${HAVE_CUPTI} := ${common-objs}
target-lscc-${HAVE_LCPTI} := $(patsubst %,%-luca,$(common-objs))

CFLAGS_NVCC := -I../
CFLAGS_LSCC := -I../

include main.mk

# $1: obj name
# $2: deps
define pti_obj
${1}: ${OUTPUT}${1}.cu.o ${2}
${1}-luca: ${OUTPUT}${1}.luca.o ${2}
endef

$(foreach obj, ${common-objs}, $(eval $(call pti_obj,${obj})))
