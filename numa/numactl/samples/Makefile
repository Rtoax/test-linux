# SPDX-License-Identifier: GPL-3.0
include numactl.mk

target-y += numa_alloc
target-y += numa_available
target-y += numa_max_node
target-y += numa_max_possible_node
target-y += numa_node_size64
target-y += numa_node_size
target-y += numa_pagesize
target-y += numa_preferred
target-y += migrate_pages

LDFLAGS += -lnuma

CFLAGS += -DNUMACTL_VERSION_MAJOR=${NUMACTL_VERSION_MAJOR}
CFLAGS += -DNUMACTL_VERSION_MINOR=${NUMACTL_VERSION_MINOR}
CFLAGS += -DNUMACTL_VERSION_PATCH=${NUMACTL_VERSION_PATCH}

# FIXME:
CFLAGS_numa_node_size := -Wno-incompatible-pointer-types
CFLAGS_numa_node_size64 := -Wno-incompatible-pointer-types

include main.mk
