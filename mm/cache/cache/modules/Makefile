include ../../../../tlbuild.mk


obj-m += flush.o

PWD := $(shell pwd)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build


default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) clean
