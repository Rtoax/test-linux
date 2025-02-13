SHELL = bash
include ../../../tlbuild.mk


obj-m += in_task.o
obj-m += preempt_count.o

KERNELDIR=/lib/modules/`uname -r`/build

all:
	${Q}make -C $(KERNELDIR) M=$(PWD) modules
clean:
	${Q}make -C $(KERNELDIR) M=$(PWD) clean
