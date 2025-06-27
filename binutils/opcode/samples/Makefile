# SPDX-License-Identifier: GPL-3.0
TARGETS := disassemble_init_for_target

CFLAGS :=
CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable

include ../../../elf/pie.mk
include ../../binutils.mk

CFLAGS += -DBINUTILS_VERSION_MAJOR=${BINUTILS_VERSION_MAJOR}
CFLAGS += -DBINUTILS_VERSION_MINOR=${BINUTILS_VERSION_MINOR}

LDFLAGS += -lopcodes -lbfd

include ../../../template/main.mk

disassemble_init_for_target: disassemble_init_for_target.o
