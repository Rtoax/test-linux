# SPDX-License-Identifier: GPL-3.0
include ./elf.mk

sub-dir := got
sub-dir += library
sub-dir += plt
sub-dir += pie

target-y := macro
target-y += rewrite-elf64

include ../template/main.mk

macro: macro.o
rewrite-elf64: rewrite-elf64.o
