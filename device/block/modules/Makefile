obj-m += gendisk.o

CURRENT_PATH := $(shell pwd)
LINUX_KERNEL_PATH := /lib/modules/`uname -r`/build

all:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
