SHELL = bash
include ../../tlbuild.mk


ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif
obj-m += kdb_hello.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
