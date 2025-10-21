# SPDX-License-Identifier: GPL-3.0
target-y := R_386_32

CC := gcc
include ../../../../compiler/compiler.mk

ifneq (${CC_M32},1)
  $(warning ${CC} not support -m32)
  target-y :=
endif

CFLAGS += -I../

CFLAGS += -m32
LDFLAGS += -m32

include ../../../../template/main.mk

R_386_32: R_386_32.o
