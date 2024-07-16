SHELL = bash

CC = gcc
CFLAGS := -Werror -Wall -pthread
LDFLAGS := -pthread

L3_CACHELINE_SIZE=$(shell cat /sys/devices/system/cpu/cpu1/cache/index3/coherency_line_size 2>/dev/null)
ifeq ($(L3_CACHELINE_SIZE),)
L3_CACHELINE_SIZE=64
endif

CFLAGS += -DL3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE)

TARGETS := struct

build: ${TARGETS}
	@echo "  INFO  struct, L3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE)"

struct: struct.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@rm -f *.o *.d ${TARGETS}
