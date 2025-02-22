
obj-m += wait_event_interruptible.o
obj-m += waitqueue.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	${Q}make -C $(KERNELDIR) M=$(PWD) modules
clean:
	${Q}make -C $(KERNELDIR) M=$(PWD) clean
