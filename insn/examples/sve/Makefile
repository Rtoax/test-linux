# SPDX-License-Identifier: GPL-3.0
CC := gcc
CFLAGS :=

# Cross compile
include ../../../compiler/cross-compile.mk
# All CC set done here
include ../../../compiler/compiler.mk

target-y :=
target-y += neon-sve

target-${feature-sve2} += sve-width
target-${feature-sve2} += add_array
target-${feature-sve2} += svaddlb

CFLAGS += -march=armv8-a+sve+sve2
CFLAGS += -DCPU_HAVE_NEON=1
CFLAGS += -DCPU_HAVE_SVE=1

include ../../../template/main.mk

sve-width: sve-width.o
add_array: add_array.o
svaddlb: svaddlb.o
neon-sve: neon-sve.o
