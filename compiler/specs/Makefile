TARGETS :=
TARGETS += hello

TARGETS_POST := test0

CFLAGS :=
CFLAGS += -specs=$(shell pwd)/definitions
CFLAGS += -specs=$(shell pwd)/definitions2

include ../../template/main.mk

hello: hello.o

test0:
	$(Q)$(CC) $(CFLAGS) -dumpspecs
