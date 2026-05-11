# SPDX-License-Identifier: GPL-3.0
include binutils.mk
include zstd.mk

target-y += disassemble_init_for_target
target-y += disassembler

CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable
CFLAGS += ${binutils-cflags}

LDFLAGS += -lopcodes -lbfd
ifeq (${HAVE_LIBZSTD},y)
  LDFLAGS += -lzstd
endif
