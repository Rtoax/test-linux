SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m += map_driver.o

PWD := $(shell pwd)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

MYDEVICE=mapnopage

default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules
	@gcc ./maptest_read.c -o read.out
	@gcc ./maptest_write.c -o write.out

insmod:
	sudo insmod map_driver.ko

mknod:
	sudo mknod /dev/$(MYDEVICE) c 111 0

clean:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) clean
	${Q}rm -f read.out write.out
	sudo rm -f /dev/$(MYDEVICE)
