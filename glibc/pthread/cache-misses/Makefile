CC = clang
CFLAGS := -Werror -Wall -pthread

L3_CACHELINE_SIZE=$(shell cat /sys/devices/system/cpu/cpu1/cache/index3/coherency_line_size)

CFLAGS += -DL3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE)

TARGETS := struct

build: ${TARGETS}
	@echo "Compile struct, L3_CACHELINE_SIZE=$(L3_CACHELINE_SIZE)"

struct: struct.o

clean:
	@rm -f *.o *.d ${TARGETS}
