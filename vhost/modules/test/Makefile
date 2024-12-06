SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m += vhost_test.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules
clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean

insmod:
	sudo modprobe vhost
	sudo insmod vhost_test.ko

rmmod:
	sudo rmmod vhost_test

sync:
	cp /home/rongtao/Git/linux/drivers/vhost/test.c .
	cp /home/rongtao/Git/linux/drivers/vhost/test.h .
	cp /home/rongtao/Git/linux/drivers/vhost/vhost.h .
