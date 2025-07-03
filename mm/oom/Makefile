TARGETS := oom
TARGETS += popen

CFLAGS_popen = -DPOPEN=1

include ../../template/main.mk

oom.o: oom_helpers.h
popen.o: oom_helpers.h
oom_helpers.o: oom_helpers.h

oom: oom.o oom_helpers.o
popen: popen.o oom_helpers.o
