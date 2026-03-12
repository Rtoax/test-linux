# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include cestc/luca.mk
include compiler.mk

common-objs := vpu

target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))
