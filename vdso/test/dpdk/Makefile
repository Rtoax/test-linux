SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


# Rong Tao, 2022.05.09

ARCH=$(shell uname -m)

ifeq (${ARCH}, x86_64)
TARGET+=tsc_freq_arch.o tsc_freq.o
else
 ifeq (${ARCH}, aarch64)
 TARGET+=
 else
 $(error Not support arch.)
 endif
endif

all: ${TARGET}

tsc_freq_arch.o:
	gcc -c tsc_freq_arch.c

tsc_freq.o:
	gcc -c tsc_freq.c

test:
	gcc tsc_freq_arch.c -o tsc_freq_arch.out -DTEST
	gcc tsc_freq.c -o tsc_freq.out -DTEST

clean:
	rm -f *.o *.out
