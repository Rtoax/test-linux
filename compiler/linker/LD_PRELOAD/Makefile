# SPDX-License-Identifier: GPL-3.0
include ../../compiler.mk

# Compile to dynamic library.
CFLAGS_PIC := -fPIC

targets :=
targets-libso :=

targets += main
ifeq ($(CC_-mfentry),1)
  targets += fentry
endif

targets-libso += libmcount-nop.so
targets-libso += libconstructor-obj.so

targets-test := test0

CFLAGS_main := -pg
CFLAGS_fentry := -pg -mfentry
CFLAGS_mcount-nop := ${CFLAGS_PIC}
CFLAGS_constructor-obj := ${CFLAGS_PIC}

include ../../../template/main.mk

main: main.o
fentry: fentry.o
libmcount-nop.so: mcount-nop.so.o
libconstructor-obj.so: constructor-obj.so.o

test0:
	$(Q)LD_PRELOAD=./libmcount-nop.so ./main
	$(Q)LD_PRELOAD=./libmcount-nop.so ./fentry
	$(Q)LD_PRELOAD=./libconstructor-obj.so ./main
