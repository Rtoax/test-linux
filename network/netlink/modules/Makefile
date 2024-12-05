SHELL = bash

obj-m += netlink_kernel.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

TARGETS := netlink_user

all: ${TARGETS}
	@make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	@make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	rm  -rf ${TARGETS} *.d *.o
