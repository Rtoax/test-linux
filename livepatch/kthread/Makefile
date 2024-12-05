SHELL = bash

# Copyright (C) Rong Tao
include /boot/config-$(shell uname -r)

LIVEPATCH:=

ifeq ($(CONFIG_LIVEPATCH),y)
LIVEPATCH=m
endif
obj-$(LIVEPATCH) += kthread.o
obj-$(LIVEPATCH) += patchkthread.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
