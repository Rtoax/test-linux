# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include cuda.mk
include rocm.mk
include ../../../metax/hpcc.mk
include ../../../cestc/luca.mk

common-objs := version

# NVIDIA CUDA
target-nvcc-${HAVE_NCCL} := ${common-objs}
target-hipcc-${HAVE_RCCL} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))

include main.mk

# $1 - program name
define nccl_obj
${1}: $${OUTPUT}${1}.cu.o
${1}-hip: $${OUTPUT}${1}.hip.o
${1}-hpcc: $${OUTPUT}${1}.hpcc.o
${1}-luca: $${OUTPUT}${1}.luca.o
endef

$(eval $(call nccl_obj,version))
