CC := gcc
CFLAGS := -pthread
LDFLAGS := -pthread

VIRT_TYPE ?= $(shell systemd-detect-virt)

LEVEL3_CACHE_LINESIZE :=
DEFAULT_LEVEL3_CACHE_LINESIZE = 64
SYS_DEV_LEVEL3_CACHE_LINESIZE = $(shell cat /sys/devices/system/cpu/cpu1/cache/index3/coherency_line_size 2>/dev/null || true)
CONF_LEVEL3_CACHE_LINESIZE = $(shell getconf LEVEL3_CACHE_LINESIZE 2>/dev/null || true)

ifeq ($(SYS_DEV_LEVEL3_CACHE_LINESIZE),0)
  $(warning Not found L3 cache in /sys/devices/system/cpu)
else ifeq (${SYS_DEV_LEVEL3_CACHE_LINESIZE},)
  LEVEL3_CACHE_LINESIZE := ${DEFAULT_LEVEL3_CACHE_LINESIZE}
else
  LEVEL3_CACHE_LINESIZE := ${SYS_DEV_LEVEL3_CACHE_LINESIZE}
endif

ifeq ($(CONF_LEVEL3_CACHE_LINESIZE),0)
  $(warning Not found L3 cache with getconf command)
else
  LEVEL3_CACHE_LINESIZE=${CONF_LEVEL3_CACHE_LINESIZE}
endif

ifneq ($(SYS_DEV_LEVEL3_CACHE_LINESIZE),$(CONF_LEVEL3_CACHE_LINESIZE))
  $(warning Bad L3 cache linesize)
endif

ifeq ($(LEVEL3_CACHE_LINESIZE),)
  ifneq (${VIRT_TYPE},none)
    $(warning Bad L3 cache linesize, use default value in VM)
    LEVEL3_CACHE_LINESIZE = $(DEFAULT_LEVEL3_CACHE_LINESIZE)
  else
    $(error Bad L3 cache linesize, your machine don't have L3?!?!?)
  endif
endif

$(info LEVEL3_CACHE_LINESIZE=$(LEVEL3_CACHE_LINESIZE))

CFLAGS += -DLEVEL3_CACHE_LINESIZE=$(LEVEL3_CACHE_LINESIZE)

targets := struct

include ../../../template/main.mk

struct: struct.o
