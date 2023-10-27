TARGETS := mode_strict

CC = clang
CFLAGS :=

mode_strict: mode_strict.o seccomp.o

all: ${TARGETS}

clean:
	rm -f ${TARGETS} *.o
