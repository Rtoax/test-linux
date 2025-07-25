# SPDX-License-Identifier: GPL-3.0
include ./elf.mk

sub-dir := got
sub-dir += library
sub-dir += plt
sub-dir += pie

targets :=
targets += macro

include pie.mk

include ../template/main.mk

macro: macro.o
