obj-m += wait_event_interruptible.o
obj-m += waitqueue.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

build:
	${Q}make -C $(KERNELDIR) M=$(PWD) modules
test:
clean:
	${Q}make -C $(KERNELDIR) M=$(PWD) clean
