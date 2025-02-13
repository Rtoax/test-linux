SHELL = bash
include ../../tlbuild.mk


obj-m := multifile.o
multifile-objs := main.o foo.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	${Q}make -C $(KERNELDIR) M=$(PWD) modules
clean:
	${Q}make -C $(KERNELDIR) M=$(PWD) clean
