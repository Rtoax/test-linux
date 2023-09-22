ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
obj-m += currentel.o
endif

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	make -C ${KERNELDIR} M=$(PWD) clean
