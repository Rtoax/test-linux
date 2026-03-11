# SPDX-License-Identifier: GPL-3.0
include compiler.mk

target-y += main
target-${feature-mfentry} += fentry

target-libso-y += libmcount-nop.so
target-libso-y += libconstructor-obj.so

target-post-y := post0

libmcount-nop.so-objs := mcount-nop.so.o
libconstructor-obj.so-objs := constructor-obj.so.o

# Compile to dynamic library.
CFLAGS_PIC := -fPIC

CFLAGS_main := -pg
CFLAGS_fentry := -pg -mfentry
CFLAGS_mcount-nop := ${CFLAGS_PIC}
CFLAGS_constructor-obj := ${CFLAGS_PIC}

include main.mk

post0:
	$(Q)LD_PRELOAD=./libmcount-nop.so ./main
	$(Q)LD_PRELOAD=./libmcount-nop.so ./fentry
	$(Q)LD_PRELOAD=./libconstructor-obj.so ./main
