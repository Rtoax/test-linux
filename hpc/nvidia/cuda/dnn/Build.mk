# SPDX-License-Identifier: GPL-3.0
include nvidia/cuda.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk

common-objs := version

target-nvcc-${HAVE_CUDNN} := ${common-objs}
target-hipcc-${HAVE_HIPDNN} := $(patsubst %,%-hip,$(common-objs))
target-htcc-${HAVE_HCDNN} := $(patsubst %,%-hpcc,$(common-objs))
target-lscc-${HAVE_LCDNN} := $(patsubst %,%-luca,$(common-objs))

$(foreach obj, ${common-objs}, \
  $(eval ${obj}-luca-objs := ${obj}.luca.o) \
  $(eval ${obj}-hpcc-objs := ${obj}.hpcc.o) \
  $(eval ${obj}-hip-objs := ${obj}.hip.o) \
)
