# SPDX-License-Identifier: GPL-3.0
include binutils.mk

target-y := disassemble_init_for_target

CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable
CFLAGS += -DBINUTILS_VERSION_MAJOR=${BINUTILS_VERSION_MAJOR}
CFLAGS += -DBINUTILS_VERSION_MINOR=${BINUTILS_VERSION_MINOR}

LDFLAGS += -lopcodes -lbfd

include main.mk

disassemble_init_for_target: disassemble_init_for_target.o
