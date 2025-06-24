TARGETS :=
TARGETS += getrlimit setrlimit ulimit prlimit
TARGETS += fork-inherit
TARGETS += getrusage vlimit

CFLAGS :=
CFLAGS += -pthread

include ../../../template/main.mk

getrlimit: getrlimit.o resource_helpers.o
setrlimit: setrlimit.o resource_helpers.o
prlimit: prlimit.o resource_helpers.o
ulimit: ulimit.o
fork-inherit: fork-inherit.o resource_helpers.o
getrusage: getrusage.o resource_helpers.o
vlimit: vlimit.o
