SHELL = bash
include ../../tlbuild.mk


ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif
ifeq ($(CONFIG_FPROBE),y)
obj-m += fprobe_example.o
endif

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
