include ../../../tlbuild.mk



TARGETS := test-1

test-1: test-1.o bitmask.o

DEBUG := yes
CC := gcc

CFLAGS :=

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

test: ${TARGETS}
	./test-1 >/dev/null

clean:
	rm -f ${TARGETS} *.o *.d
