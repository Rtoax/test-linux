TARGETS :=
TARGETS += epoll
TARGETS += eventfd_read
TARGETS += eventfd-irq
TARGETS += eventfd-latency

include ../../../template/main.mk

epoll: epoll.o
eventfd_read: eventfd_read.o utils.o
eventfd-irq: eventfd-irq.o utils.o
eventfd-latency: eventfd-latency.o utils.o
