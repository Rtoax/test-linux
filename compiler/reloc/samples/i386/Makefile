# SPDX-License-Identifier: GPL-3.0

CC := gcc
include ../../../../compiler/compiler.mk

target-${CC_M32} := R_386_32

CFLAGS += -I../
CFLAGS += -m32
LDFLAGS += -m32

include ../../../../template/main.mk

R_386_32: R_386_32.o
