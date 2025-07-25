targets :=
targets += epoll
targets += eventfd_read
targets += eventfd-irq
targets += eventfd-latency

include ../../../template/main.mk

epoll: epoll.o
eventfd_read: eventfd_read.o utils.o
eventfd-irq: eventfd-irq.o utils.o
eventfd-latency: eventfd-latency.o utils.o
