# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include cestc/luca.mk
include compiler.mk

common-objs := vpu

target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))

include main.mk

define vpu_obj
${1}-luca: ${OUTPUT}${1}.luca.o
endef

$(foreach obj, ${common-objs}, $(eval $(call vpu_obj,${obj})))
