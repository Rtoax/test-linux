target-y += epoll
target-y += eventfd_read
target-y += eventfd-irq
target-y += eventfd-latency

eventfd_read-objs := utils.o
eventfd-irq-objs := utils.o
eventfd-latency-objs := utils.o
