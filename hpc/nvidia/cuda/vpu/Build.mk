# SPDX-License-Identifier: GPL-3.0
include cestc/luca.mk
include compiler.mk

common-objs := vpu

target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))

$(foreach obj, ${common-objs}, \
  $(eval ${obj}-luca-objs := ${obj}.luca.o) \
)
