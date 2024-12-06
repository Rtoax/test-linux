SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m:= paging_lowmem.o
PWD:= $(shell pwd)
KERNELDIR:= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C $(KERNELDIR)  M=$(PWD) modules
clean:
	${Q}make -C $(KERNELDIR)  M=$(PWD) clean
