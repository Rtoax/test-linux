SHELL = bash

obj-m := myfs.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

all:
	@make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

test:
	@echo >/dev/null

clean:
	@make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
