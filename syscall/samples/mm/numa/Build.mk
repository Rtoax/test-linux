# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
include numactl.mk

target-${HAVE_LIBNUMA} += mbind
target-${HAVE_LIBNUMA} += move_pages
target-${HAVE_LIBNUMA} += migrate_pages
target-${HAVE_LIBNUMA} += get_mempolicy

mbind-objs := numa_helpers.o
move_pages-objs := numa_helpers.o
get_mempolicy-objs := numa_helpers.o

CFLAGS += -pthread
LDFLAGS += -lnuma

CFLAGS_mbind := -DALLOC_WITH_MMAP=1
#CFLAGS_mbind := -DALLOC_WITH_MALLOC=1
#CFLAGS_mbind := -DALLOC_WITH_POSIX_MEMALIGN=1

CFLAGS_move_pages := -DALLOC_WITH_MALLOC=1
