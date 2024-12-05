SHELL = bash

obj-m:= paging_lowmem.o
PWD:= $(shell pwd)
KERNELDIR:= /lib/modules/$(shell uname -r)/build

all:
	@make -C $(KERNELDIR)  M=$(PWD) modules
clean:
	@make -C $(KERNELDIR)  M=$(PWD) clean
