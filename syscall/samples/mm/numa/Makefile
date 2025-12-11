# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2025 Rong Tao
include numactl.mk

target-${HAVE_LIBNUMA} += mbind
target-${HAVE_LIBNUMA} += move_pages
target-${HAVE_LIBNUMA} += migrate_pages
target-${HAVE_LIBNUMA} += get_mempolicy

CFLAGS += -pthread
CFLAGS += -O0
LDFLAGS += -lnuma

CFLAGS_mbind := -DALLOC_WITH_MMAP=1
#CFLAGS_mbind := -DALLOC_WITH_MALLOC=1
#CFLAGS_mbind := -DALLOC_WITH_POSIX_MEMALIGN=1

CFLAGS_move_pages := -DALLOC_WITH_MALLOC=1

include main.mk

numa_helpers.o: numa_helpers.h
mbind: mbind.o numa_helpers.o
move_pages: move_pages.o numa_helpers.o
migrate_pages: migrate_pages.o
get_mempolicy: get_mempolicy.o numa_helpers.o
