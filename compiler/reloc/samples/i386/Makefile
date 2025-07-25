# SPDX-License-Identifier: GPL-3.0
targets :=
targets += R_386_32

CC := gcc
include ../../../../compiler/compiler.mk

ifneq (${CC_M32},1)
  $(warning ${CC} not support -m32)
  targets :=
endif

CFLAGS += -I../

CFLAGS += -m32
LDFLAGS += -m32

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
ifndef PIE
  NOPIE ?= 1
endif
include ../../../../elf/pie.mk

include ../../../../template/main.mk

R_386_32: R_386_32.o
