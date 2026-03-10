target-y += getrlimit setrlimit ulimit prlimit
target-y += fork-inherit
target-y += getrusage vlimit

getrlimit-objs := resource_helpers.o
setrlimit-objs := resource_helpers.o
prlimit-objs := resource_helpers.o
fork-inherit-objs := resource_helpers.o
getrusage-objs := resource_helpers.o

CFLAGS += -pthread

include main.mk
