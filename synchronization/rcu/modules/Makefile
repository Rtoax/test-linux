SHELL = bash

obj-m += rcu.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	@make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	@make -C ${KERNELDIR} M=$(PWD) clean
