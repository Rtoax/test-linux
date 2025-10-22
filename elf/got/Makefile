# SPDX-License-Identifier: GPL-3.0
include ../../compiler/compiler.mk

target-y :=
target-y += _GLOBAL_OFFSET_TABLE_
target-${CC_M32} += _GLOBAL_OFFSET_TABLE_-32

CFLAGS := -O0 -g -ggdb

# If only -fpic in CFLAGS, 'Illegal instruction (core dumped)' on x86

CFLAGS__GLOBAL_OFFSET_TABLE_-32 := -m32 -DM32=1
LDFLAGS__GLOBAL_OFFSET_TABLE_-32 := -m32

include ../../template/main.mk

_GLOBAL_OFFSET_TABLE_: _GLOBAL_OFFSET_TABLE_.o
_GLOBAL_OFFSET_TABLE_-32: _GLOBAL_OFFSET_TABLE_-32.o
