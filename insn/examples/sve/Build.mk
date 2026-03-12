# SPDX-License-Identifier: GPL-3.0
include cross-compile.mk
# All CC set done here
include compiler.mk
include cpu.mk

target-y += neon-sve

target-${feature-sve2} += sve-width
target-${feature-sve2} += add_array
target-${feature-sve2} += svaddlb

CFLAGS += -march=armv8-a+sve+sve2
CFLAGS += ${cpu-feature-cflags}
