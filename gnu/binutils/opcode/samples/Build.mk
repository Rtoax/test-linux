# SPDX-License-Identifier: GPL-3.0
include binutils.mk

target-y := disassemble_init_for_target

CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable
CFLAGS += ${binutils-cflags}

LDFLAGS += -lopcodes -lbfd
