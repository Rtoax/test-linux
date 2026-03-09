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

default-l3linesize := 64
sysfs-l3linesize := $(shell cat /sys/devices/system/cpu/cpu0/cache/index3/coherency_line_size 2>/dev/null || true)
getconf-l3linesize := $(shell getconf LEVEL3_CACHE_LINESIZE 2>/dev/null || true)

ifeq ($(sysfs-l3linesize),0)
  $(warning Not found L3 cache in /sys/devices/system/cpu/cpu0/)
else ifneq (${sysfs-l3linesize},)
  CPU_L3LINESIZE := ${sysfs-l3linesize}
endif

ifeq (${CPU_L3LINESIZE},)
  ifeq ($(getconf-l3linesize),0)
    $(warning Not found L3 cache with getconf command)
  else
    CPU_L3LINESIZE := ${getconf-l3linesize}
  endif
endif

ifeq ($(CPU_L3LINESIZE),)
  CPU_L3LINESIZE = $(default-l3linesize)
endif

ifdef DEBUG
  $(info CPU_L3LINESIZE = $(CPU_L3LINESIZE))
endif

cpu-cflags += -DCPU_L3LINESIZE=$(CPU_L3LINESIZE)

export cpu-cflags
export CPU_L3LINESIZE

endif
