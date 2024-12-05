SHELL = bash

obj-m += get_unmapped_area.o
obj-m += address.o

PWD := $(shell pwd)
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	@make -C $(KDIR) M=$(PWD) modules
clean:
	@make -C $(KDIR) M=$(PWD) clean
