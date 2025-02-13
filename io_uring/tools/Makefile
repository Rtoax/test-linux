SHELL = bash
include ../../tlbuild.mk


# SPDX-License-Identifier: GPL-2.0
# Makefile for io_uring test tools
CFLAGS += -Wall -Wextra -g -D_GNU_SOURCE
LDLIBS += -lpthread

all: io_uring-cp.out \
	 io_uring-bench.out \
	 io_uring-latency.out
	 
%: %.c
	${Q}$(CC) $(CFLAGS) -o $@ $^

io_uring-bench.out: syscall.o io_uring-bench.o
	${Q}$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

io_uring-cp.out: setup.o syscall.o queue.o io_uring-cp.o
	${Q}$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

io_uring-latency.out:  setup.o syscall.o queue.o io_uring-latency.o
	${Q}$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
	
clean:
	$(RM) io_uring-cp io_uring-bench *.o *.out

.PHONY: all clean
