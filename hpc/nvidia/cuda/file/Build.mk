# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
include nvidia/cuda.mk
include cestc/luca.mk
include metax/hpcc.mk

common-objs := hello
common-objs += gdsio

target-nvcc-${HAVE_CUFILE} := ${common-objs}
target-lscc-${HAVE_LCFILE} := $(patsubst %,%-luca,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))

$(foreach obj, ${common-objs}, \
  $(eval ${obj}-luca-objs := ${obj}.luca.o) \
  $(eval ${obj}-hpcc-objs := ${obj}.hpcc.o) \
  $(eval ${obj}-hip-objs := ${obj}.hip.o) \
)

# Ignore warning: array designators are a C99 extension
CFLAGS_LSCC += -Wno-c99-designator
LDFLAGS_NVCC += -lpthread
