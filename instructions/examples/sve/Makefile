# SPDX-License-Identifier: GPL-3.0
CC := gcc
CFLAGS :=
RUN_PFX :=

# Cross compile
include ../../../compiler/cross-compile.mk
# All CC set done here
include ../../../compiler/compiler.mk

targets :=
targets += neon-sve

feature-sve2 := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))
ifeq (${feature-sve2},1)
  $(info feature-sve2 = ${feature-sve2})

  targets += sve-width
  targets += add_array
  targets += svaddlb

  CFLAGS += -march=armv8-a+sve+sve2
  CFLAGS += -DCPU_HAVE_NEON=1
  CFLAGS += -DCPU_HAVE_SVE=1
endif

include ../../../template/main.mk

sve-width: sve-width.o
add_array: add_array.o
svaddlb: svaddlb.o
neon-sve: neon-sve.o
