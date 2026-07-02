# SPDX-License-Identifier: GPL-3.0
include numactl.mk

subdir-${HAVE_LIBNUMA} := numactl

prep-y := numa_mem.h
target-y := numa_mem
target-y += memory
target-liba-y := numa.a

numa.a-deps := numa_mem.h
numa.a-objs := numa_mem.a.o

numa_mem.a.o-deps := numa_mem.h

CFLAGS += -g
LDFLAGS += -lnuma

CFLAGS_numa_mem := -DTEST_MAIN=1
