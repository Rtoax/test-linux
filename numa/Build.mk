# SPDX-License-Identifier: GPL-3.0
include numactl.mk

subdir-${HAVE_LIBNUMA} := numactl

prep-y := numa_mem.h
target-y := numa_mem
target-y += memory
target-liba-y := numa.a
target-libso-y := numa.so

numa.a-objs := numa_mem.a.o
numa.so-objs := numa_mem.so.o

numa_mem.a.o-deps := numa_mem.h
numa_mem.so.o-deps := numa_mem.h

CFLAGS += -g
LDFLAGS += -lnuma

CFLAGS_numa_mem := -DTEST_MAIN=1
