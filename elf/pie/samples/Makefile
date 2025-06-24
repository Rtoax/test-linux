# SPDX-License-Identifier: GPL-3.0
include ../../elf.mk

TARGETS := hello
TARGETS += hello-pie
TARGETS += is_pie

TARGETS_LIBA := proc_helpers.a

CFLAGS_hello += -no-pie
LDFLAGS_hello += -no-pie

CFLAGS_hello-pie := -fpie
LDFLAGS_hello-pie := -pie

LDFLAGS_is_pie := -lelf

include ../../../template/main.mk

proc_helpers.a.o: proc_helpers.h
proc_helpers.a: proc_helpers.a.o

hello: hello.o proc_helpers.a
hello-pie: hello-pie.o proc_helpers.a
is_pie: is_pie.o
