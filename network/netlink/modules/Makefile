obj-m += netlink_kernel.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

target-y := netlink_user

all: ${target-y}
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	rm  -rf ${target-y} *.d *.o
