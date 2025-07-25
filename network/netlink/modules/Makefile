obj-m += netlink_kernel.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

targets := netlink_user

all: ${targets}
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	rm  -rf ${targets} *.d *.o
