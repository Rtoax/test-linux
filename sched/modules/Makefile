SHELL = bash

obj-m += sched_debug.o
obj-m += uninterruptible.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	@make -C $(KERNELDIR) M=$(PWD) modules

clean:
	@make -C $(KERNELDIR) M=$(PWD) clean
