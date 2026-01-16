obj-$(CONFIG_KGDB_KDB) += kdb_hello.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
