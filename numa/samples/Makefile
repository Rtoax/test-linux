# SPDX-License-Identifier: GPL-3.0
include ../numactl.mk

LIBNUMA_HDR = /usr/include/numa.h

TARGETS :=
TARGETS += numa_alloc
TARGETS += numa_available
TARGETS += numa_max_node
TARGETS += numa_max_possible_node
TARGETS += numa_node_size64
TARGETS += numa_node_size
TARGETS += numa_pagesize
TARGETS += numa_preferred
TARGETS += migrate_pages

ifeq ($(wildcard $(LIBNUMA_HDR)),)
  TARGETS :=
  $(warning "ERROR: Must install numactl development header")
endif

CFLAGS := -Werror -Wall
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
