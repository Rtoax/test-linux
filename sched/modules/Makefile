

obj-m += sched_debug.o
obj-m += uninterruptible.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	${Q}make -C $(KERNELDIR) M=$(PWD) modules

clean:
	${Q}make -C $(KERNELDIR) M=$(PWD) clean
