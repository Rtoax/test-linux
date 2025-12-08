# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include cuda.mk
include luca.mk
include hpcc.mk

common-objs := hello
common-objs += gdsio

target-nvcc-${HAVE_CUFILE} := ${common-objs}
target-lscc-${HAVE_LCFILE} := $(patsubst %,%-luca,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))

include main.mk

# $1: obj name
# $2: deps
define file_obj
${1}: ${OUTPUT}${1}.cu.o ${2}
${1}-luca: ${OUTPUT}${1}.luca.o ${2}
${1}-hpcc: ${OUTPUT}${1}.hpcc.o ${2}
endef

$(foreach obj, ${common-objs}, $(eval $(call file_obj,${obj})))
