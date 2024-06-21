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
	@echo "CC struct, L3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE)"

struct: struct.o

clean:
	@rm -f *.o *.d ${TARGETS}
