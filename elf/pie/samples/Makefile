# SPDX-License-Identifier: GPL-3.0
include ../../elf.mk

TARGETS := hello
TARGETS += hello-pie
TARGETS += is_pie

LIBPROCFS_DIR := ../../../fs/procfs/

CFLAGS += -I${LIBPROCFS_DIR}

CFLAGS_hello += -no-pie
LDFLAGS_hello += -no-pie
CFLAGS_hello-pie := -fpie
LDFLAGS_hello-pie := -pie
CFLAGS_proc := -fpie
LDFLAGS_is_pie := -lelf

include ../../../template/main.mk

include ${LIBPROCFS_DIR}/procfs-lib-target.mk

hello: hello.o libtest-linux-procfs.a
hello-pie: hello-pie.o libtest-linux-procfs.a
is_pie: is_pie.o
