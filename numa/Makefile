# SPDX-License-Identifier: GPL-3.0
include numactl.mk

sub-dir := samples

TARGETS := numa_mem
TARGETS_LIBA := libtest-linux-numa.a

CFLAGS += -g
LDFLAGS += -lnuma

CFLAGS_numa_mem := -DTEST_MAIN=1

TARGETS_PREP := numa_mem.h

include ../template/main.mk

numa_mem.h:
	${Q}./info.sh c

numa_mem: numa_mem.o
libtest-linux-numa.a: numa_mem.h numa_mem.a.o
