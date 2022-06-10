obj-m += wait_event_interruptible.o
obj-m += waitqueue.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	make -C $(KERNELDIR) M=$(PWD) clean
