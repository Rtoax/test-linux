SHELL = bash

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif
obj-m += oom_notifier.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	@make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	@make -C ${KERNELDIR} M=$(PWD) clean
