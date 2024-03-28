TARGETS := mode_strict
TARGETS += mode_filter

CC = clang
CFLAGS :=

all: ${TARGETS}

mode_strict: mode_strict.o seccomp.o
mode_filter: mode_filter.o

clean:
	rm -f ${TARGETS} *.o
