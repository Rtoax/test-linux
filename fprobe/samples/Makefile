SHELL = bash

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif
ifeq ($(CONFIG_FPROBE),y)
obj-m += fprobe_example.o
endif

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	@make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	@make -C ${KERNELDIR} M=$(PWD) clean
