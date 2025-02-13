include ../../../tlbuild.mk


TARGETS :=
ifeq ($(shell uname -m),x86_64)
TARGETS += test
endif

CC = gcc
CFLAGS := -O0

build: ${TARGETS}

test: test.o breakfast.o

clean:
	rm -rf $(TARGETS) *.o
