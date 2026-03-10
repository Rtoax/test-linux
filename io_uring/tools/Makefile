target-y := io_uring-cp
target-y += io_uring-bench
target-y += io_uring-latency

io_uring-bench-objs := syscall.o
io_uring-cp-objs := setup.o syscall.o queue.o
io_uring-latency-objs :=  setup.o syscall.o queue.o

CFLAGS += -Wextra -g

include main.mk
