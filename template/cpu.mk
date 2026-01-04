# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Ouput definitions:
# - CPU_VENDOR_ID=
# - CPU_L3LINESIZE=[64]
#
_CPU_MK = 1

include bits/cpu-feature.mk

CPU_VENDOR_ID := $(shell lscpu | grep ^Vendor | awk '{print $$3}')

CPU_L3LINESIZE :=

DEFAULT_L3LINESIZE := 64
SYS_DEV_L3LINESIZE := $(shell cat /sys/devices/system/cpu/cpu1/cache/index3/coherency_line_size 2>/dev/null || true)
CONF_L3LINESIZE := $(shell getconf LEVEL3_CACHE_LINESIZE 2>/dev/null || true)

ifeq ($(SYS_DEV_L3LINESIZE),0)
  $(warning Not found L3 cache in /sys/devices/system/cpu)
else ifeq (${SYS_DEV_L3LINESIZE},)
  CPU_L3LINESIZE := ${DEFAULT_L3LINESIZE}
else
  CPU_L3LINESIZE := ${SYS_DEV_L3LINESIZE}
endif

ifeq ($(CONF_L3LINESIZE),0)
  $(warning Not found L3 cache with getconf command)
else
  CPU_L3LINESIZE := ${CONF_L3LINESIZE}
endif

ifneq ($(SYS_DEV_L3LINESIZE),$(CONF_L3LINESIZE))
  $(warning Bad L3 cache linesize)
endif

ifeq ($(CPU_L3LINESIZE),)
  CPU_L3LINESIZE = $(DEFAULT_L3LINESIZE)
endif

ifdef DEBUG
  $(info CPU_L3LINESIZE = $(CPU_L3LINESIZE))
endif

CFLAGS += -DCPU_L3LINESIZE=$(CPU_L3LINESIZE)

export CPU_VENDOR_ID CPU_L3LINESIZE
