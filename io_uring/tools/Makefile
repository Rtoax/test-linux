TARGETS := io_uring-cp.out
TARGETS += io_uring-bench.out
TARGETS += io_uring-latency.out

CFLAGS += -Wextra -g

include ../../template/main.mk

io_uring-bench.out: syscall.o io_uring-bench.o
io_uring-cp.out: setup.o syscall.o queue.o io_uring-cp.o
io_uring-latency.out:  setup.o syscall.o queue.o io_uring-latency.o
