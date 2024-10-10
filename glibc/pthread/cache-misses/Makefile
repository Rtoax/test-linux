SHELL = bash

CC = gcc
CFLAGS := -Werror -Wall -pthread
LDFLAGS := -pthread

PROC_L3_CACHELINE_SIZE=$(shell cat /sys/devices/system/cpu/cpu1/cache/index3/coherency_line_size 2>/dev/null)
CONF_L3_CACHELINE_SIZE=$(shell getconf LEVEL3_CACHE_LINESIZE)

ifneq ($(PROC_L3_CACHELINE_SIZE),$(CONF_L3_CACHELINE_SIZE))
  $(error Bad L3 cache linesize)
endif

L3_CACHELINE_SIZE=${CONF_L3_CACHELINE_SIZE}

$(info L3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE))

CFLAGS += -DL3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE)

TARGETS := struct

build: ${TARGETS}
	@echo -e "  \033[1;32mDone\033[m"

struct: struct.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f *.o *.d ${TARGETS}
