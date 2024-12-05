SHELL = bash


obj-m += VMALLOC_START.o
obj-m += is_vmalloc_addr.o

PWD := $(shell pwd)
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	@make -C $(KDIR) M=$(PWD) modules
clean:
	@make -C $(KDIR) M=$(PWD) clean
