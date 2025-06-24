TARGETS :=
TARGETS += flock flock-fork flock-unlink flock-thread

CFLAGS :=

include ../../../template/main.mk

flock_helpers.o: flock_helpers.h
flock: flock.o
flock-fork: flock-fork.o flock_helpers.o
flock-unlink: flock-unlink.o
flock-thread: flock-thread.o flock_helpers.o
