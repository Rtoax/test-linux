include ../../../tlbuild.mk


obj-m:= paging_lowmem.o
PWD:= $(shell pwd)
KERNELDIR:= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C $(KERNELDIR)  M=$(PWD) modules
clean:
	${Q}make -C $(KERNELDIR)  M=$(PWD) clean
