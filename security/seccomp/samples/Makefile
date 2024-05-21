TARGETS := mode_strict
TARGETS += mode_filter
TARGETS += filter-write

CC = gcc
CFLAGS :=

all: ${TARGETS}

mode_strict: mode_strict.o seccomp.o
mode_filter: mode_filter.o
filter-write: filter-write.o

clean:
	rm -f ${TARGETS} *.o
