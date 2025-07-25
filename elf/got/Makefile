# SPDX-License-Identifier: GPL-3.0
CC := gcc

include ../../compiler/compiler.mk

targets :=
targets += _GLOBAL_OFFSET_TABLE_
ifeq ($(shell uname -m),x86_64)
  ifeq (${CC_M32},1)
    $(info ${CC} support -m32)
    targets += _GLOBAL_OFFSET_TABLE_-32
  endif
endif

CFLAGS :=
LDFLAGS :=
CFLAGS += -O0 -g -ggdb

ifdef STATIC
  LDFLAGS += -static
endif

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
# If only -fpic in CFLAGS, 'Illegal instruction (core dumped)' on x86
NOPIE ?= 1
include ../pie.mk

CFLAGS__GLOBAL_OFFSET_TABLE_-32 := -m32 -DM32=1
LDFLAGS__GLOBAL_OFFSET_TABLE_-32 := -m32

include ../../template/main.mk

_GLOBAL_OFFSET_TABLE_: _GLOBAL_OFFSET_TABLE_.o
_GLOBAL_OFFSET_TABLE_-32: _GLOBAL_OFFSET_TABLE_-32.o
