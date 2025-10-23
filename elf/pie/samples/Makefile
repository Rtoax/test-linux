# SPDX-License-Identifier: GPL-3.0
__USE_PROC_HELPERS__ = y

include ../../elf.mk

target-y := hello
target-y += hello-pie
target-y += is_pie

CFLAGS_hello += -no-pie
LDFLAGS_hello += -no-pie

CFLAGS_hello-pie := -fpie
LDFLAGS_hello-pie := -pie

LDFLAGS_is_pie := -lelf

include ../../../template/main.mk

hello: hello.o ${PROC_HELPERS}
hello-pie: hello-pie.o ${PROC_HELPERS}
is_pie: is_pie.o
