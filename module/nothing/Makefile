obj-m += nothing.o

KERNEL_DIR = /lib/modules/`uname -r`/build
MODULE_DIR := $(shell pwd)

build:
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules

clean:
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) clean
