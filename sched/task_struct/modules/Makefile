SHELL = bash

obj-m += task_struct.o
obj-m += init_task.o
obj-m += rculisttask.o
obj-m += next_task.o
obj-m += for_each_process.o
obj-m += dump_task.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	@make -C $(KERNELDIR) M=$(PWD) modules

clean:
	@make -C $(KERNELDIR) M=$(PWD) clean
