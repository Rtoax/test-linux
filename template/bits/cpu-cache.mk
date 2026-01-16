# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Ouput definitions:
# - CPU_L3LINESIZE=[64]
#
# Append:
# - cpu-cflags+=-DCPU_L3LINESIZE=[64]
#
ifndef _BITS_CPU_CACHE_MK
_BITS_CPU_CACHE_MK = 1

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
  $(error Bad L3 cache linesize, $(SYS_DEV_L3LINESIZE) != $(CONF_L3LINESIZE))
endif

ifeq ($(CPU_L3LINESIZE),)
  CPU_L3LINESIZE = $(DEFAULT_L3LINESIZE)
endif

ifdef DEBUG
  $(info CPU_L3LINESIZE = $(CPU_L3LINESIZE))
endif

cpu-cflags += -DCPU_L3LINESIZE=$(CPU_L3LINESIZE)

export cpu-cflags
export CPU_L3LINESIZE

endif
