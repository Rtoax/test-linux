# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
OUTPUT := .output/

include nvidia/cuda.mk
include cestc/luca.mk
include metax/hpcc.mk

common-objs := hello
common-objs += gdsio

target-nvcc-${HAVE_CUFILE} := ${common-objs}
target-lscc-${HAVE_LCFILE} := $(patsubst %,%-luca,$(common-objs))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))

# Ignore warning: array designators are a C99 extension
CFLAGS_LSCC += -Wno-c99-designator
