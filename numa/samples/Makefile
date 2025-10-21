# SPDX-License-Identifier: GPL-3.0
include ../numactl.mk

LIBNUMA_HDR = /usr/include/numa.h

target-y :=
target-y += numa_alloc
target-y += numa_available
target-y += numa_max_node
target-y += numa_max_possible_node
target-y += numa_node_size64
target-y += numa_node_size
target-y += numa_pagesize
target-y += numa_preferred
target-y += migrate_pages

ifeq ($(wildcard $(LIBNUMA_HDR)),)
  target-y :=
  $(warning "ERROR: Must install numactl development header")
endif

CFLAGS :=
LDFLAGS += -lnuma

CFLAGS += -DNUMACTL_VERSION_MAJOR=${NUMACTL_VERSION_MAJOR}
CFLAGS += -DNUMACTL_VERSION_MINOR=${NUMACTL_VERSION_MINOR}
CFLAGS += -DNUMACTL_VERSION_PATCH=${NUMACTL_VERSION_PATCH}

# FIXME:
CFLAGS_numa_node_size := -Wno-incompatible-pointer-types
CFLAGS_numa_node_size64 := -Wno-incompatible-pointer-types

include ../../template/main.mk

numa_alloc: numa_alloc.o
numa_available: numa_available.o
numa_max_node: numa_max_node.o
numa_max_possible_node: numa_max_possible_node.o
numa_node_size64: numa_node_size64.o
numa_node_size: numa_node_size.o
numa_pagesize: numa_pagesize.o
numa_preferred: numa_preferred.o
migrate_pages: migrate_pages.o
