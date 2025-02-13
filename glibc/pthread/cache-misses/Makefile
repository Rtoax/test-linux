SHELL = bash
include ../../../tlbuild.mk


CC = gcc
CFLAGS := -Werror -Wall -pthread
LDFLAGS := -pthread

VIRT_TYPE ?= $(shell systemd-detect-virt)

L3_CACHELINE_SIZE :=
DEFAULT_L3_CACHELINE_SIZE = 64
SYS_DEV_L3_CACHELINE_SIZE = $(shell cat /sys/devices/system/cpu/cpu1/cache/index3/coherency_line_size 2>/dev/null)
CONF_L3_CACHELINE_SIZE = $(shell getconf LEVEL3_CACHE_LINESIZE)

ifeq ($(SYS_DEV_L3_CACHELINE_SIZE),0)
  $(warning Not found L3 cache in /sys/devices/system/cpu)
else
  L3_CACHELINE_SIZE=${SYS_DEV_L3_CACHELINE_SIZE}
endif

ifeq ($(CONF_L3_CACHELINE_SIZE),0)
  $(warning Not found L3 cache with getconf command)
else
  L3_CACHELINE_SIZE=${CONF_L3_CACHELINE_SIZE}
endif

ifneq ($(SYS_DEV_L3_CACHELINE_SIZE),$(CONF_L3_CACHELINE_SIZE))
  $(warning Bad L3 cache linesize)
endif

ifeq ($(L3_CACHELINE_SIZE),)
  ifneq (${VIRT_TYPE},none)
    $(warning Bad L3 cache linesize, use default value in VM)
    L3_CACHELINE_SIZE = $(DEFAULT_L3_CACHELINE_SIZE)
  else
    $(error Bad L3 cache linesize, your machine don't have L3?!?!?)
  endif
endif

$(info L3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE))

CFLAGS += -DL3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE)

TARGETS := struct

build: ${TARGETS}
	@echo -e "  \033[1;32mDone\033[m"

struct: struct.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f *.o *.d ${TARGETS}
