# SPDX-License-Identifier: GPL-3.0
__USE_PROC_HELPERS__ = y

include elf.mk
include helpers.mk

target-y := hello
target-y += hello-pie
target-y += is_pie

hello-objs := ${PROC_HELPERS}
hello-pie-objs := ${PROC_HELPERS}

CFLAGS_hello += -no-pie
LDFLAGS_hello += -no-pie

CFLAGS_hello-pie := -fpie
LDFLAGS_hello-pie := -pie

LDFLAGS_is_pie := -lelf
