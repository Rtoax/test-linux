SHELL = bash
include ../../../tlbuild.mk


obj-m += get_unmapped_area.o
obj-m += address.o

PWD := $(shell pwd)
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C $(KDIR) M=$(PWD) modules
clean:
	${Q}make -C $(KDIR) M=$(PWD) clean
