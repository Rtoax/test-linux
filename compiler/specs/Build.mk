target-y += hello

target-post-y := test0

CFLAGS += -specs=$(shell pwd)/definitions
CFLAGS += -specs=$(shell pwd)/definitions2
