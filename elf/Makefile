# SPDX-License-Identifier: GPL-3.0
include ./elf.mk

subdir-y := got
subdir-y += library
subdir-y += plt
subdir-y += pie

target-y := macro
target-y += rewrite-elf64

include ../template/main.mk

macro: macro.o
rewrite-elf64: rewrite-elf64.o
