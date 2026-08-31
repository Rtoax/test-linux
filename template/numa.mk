# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Ouput definitions:
# - NUMA_NODE_COUNT=[1|2|...]
# - numa-cflags=
#
ifndef _NUMA_MK
_NUMA_MK = 1

include shell.mk

NUMA_NODE_COUNT := $(shell ls /sys/devices/system/node/ | grep -E 'node[0-9]+' | wc -w)

numa-cflags := -DNUMA_NODE_COUNT=${NUMA_NODE_COUNT}

ifdef DEBUG
  $(info NUMA_NODE_COUNT = ${NUMA_NODE_COUNT})
  $(info numa-cflags = ${numa-cflags})
endif

export NUMA_NODE_COUNT
export numa-cflags

endif
