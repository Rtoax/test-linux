# SPDX-License-Identifier: GPL-3.0
include numactl.mk

sub-dir := samples

targets := numa_mem
targets-liba := numa.a
targets-prep := numa_mem.h

CFLAGS += -g
LDFLAGS += -lnuma

CFLAGS_numa_mem := -DTEST_MAIN=1

include ../template/main.mk

numa_mem.h:
	${Q}./info.sh c

numa_mem: numa_mem.o
numa.a: numa_mem.h numa_mem.a.o
