# SPDX-License-Identifier: GPL-3.0
include numactl.mk

subdir-${HAVE_LIBNUMA} := numactl

target-y := numa_mem
target-y += memory
target-liba-y := numa.a
target-prep-y := numa_mem.h

numa.a-objs := numa_mem.h numa_mem.a.o

CFLAGS += -g
LDFLAGS += -lnuma

CFLAGS_numa_mem := -DTEST_MAIN=1

include main.mk

numa_mem.h:
	${Q}./info.sh c

numa_mem: numa_mem.o
memory: memory.o
