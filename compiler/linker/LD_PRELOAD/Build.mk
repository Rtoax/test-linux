# SPDX-License-Identifier: GPL-3.0
include compiler.mk

target-y += main
target-${feature-mfentry} += fentry

target-libso-y += libmcount-nop.so
target-libso-y += libconstructor-obj.so

post-y := post0
post-${feature-mfentry} += post0

libmcount-nop.so-objs := mcount-nop.so.o
libconstructor-obj.so-objs := constructor-obj.so.o

# Compile to dynamic library.
CFLAGS_PIC := -fPIC

CFLAGS_main := -pg
CFLAGS_fentry := -pg -mfentry
CFLAGS_SO_mcount-nop := ${CFLAGS_PIC}
CFLAGS_SO_mcount-nop += -Wno-error=frame-address
CFLAGS_SO_constructor-obj := ${CFLAGS_PIC}
