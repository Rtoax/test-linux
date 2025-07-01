obj-m += crc32c.o
ifeq ($(shell uname -m),x86_64)
  obj-m += crc32c-intel.o
endif
ifeq ($(shell uname -m),aarch64)
  obj-m += crc32c-arm64.o
endif

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

build:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
