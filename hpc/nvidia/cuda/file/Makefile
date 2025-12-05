# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include cuda.mk
include luca.mk

common-objs := hello

target-nvcc-${HAVE_CUFILE} := ${common-objs}
target-lscc-${HAVE_LCFILE} := $(patsubst %,%-luca,$(common-objs))

include main.mk

define file_obj
${1}: ${OUTPUT}${1}.cu.o
${1}-luca: ${OUTPUT}${1}.luca.o
endef

$(foreach obj, ${common-objs}, $(eval $(call file_obj,${obj})))
