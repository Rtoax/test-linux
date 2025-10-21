target-y :=
target-y += epoll
target-y += eventfd_read
target-y += eventfd-irq
target-y += eventfd-latency

include ../../../template/main.mk

epoll: epoll.o
eventfd_read: eventfd_read.o utils.o
eventfd-irq: eventfd-irq.o utils.o
eventfd-latency: eventfd-latency.o utils.o
