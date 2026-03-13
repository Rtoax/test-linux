# SPDX-License-Identifier: GPL-3.0
include compiler.mk

target-y += main
target-${feature-mfentry} += fentry

target-libso-y += libmcount-nop.so
target-libso-y += libconstructor-obj.so

target-post-y := post0
target-post-${feature-mfentry} += post0

libmcount-nop.so-objs := ${OUTPUT}mcount-nop.so.o
libconstructor-obj.so-objs := ${OUTPUT}constructor-obj.so.o

# Compile to dynamic library.
CFLAGS_PIC := -fPIC

CFLAGS_main := -pg
CFLAGS_fentry := -pg -mfentry
CFLAGS_mcount-nop := ${CFLAGS_PIC}
CFLAGS_constructor-obj := ${CFLAGS_PIC}
