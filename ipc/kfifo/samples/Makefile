include ../../../tlbuild.mk


obj-m += bytestream-example.o
obj-m += dma-example.o
obj-m += inttype-example.o
obj-m += record-example.o


ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
