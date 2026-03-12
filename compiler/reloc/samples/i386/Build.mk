# SPDX-License-Identifier: GPL-3.0
include compiler.mk

target-${CC_M32} := R_386_32

CFLAGS += -I../
CFLAGS += -m32
LDFLAGS += -m32
