SHELL = bash

obj-m += in_task.o
obj-m += preempt_count.o

KERNELDIR=/lib/modules/`uname -r`/build

all:
	@make -C $(KERNELDIR) M=$(PWD) modules
clean:
	@make -C $(KERNELDIR) M=$(PWD) clean
