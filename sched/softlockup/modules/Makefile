SHELL = bash
include ../../../tlbuild.mk


# Copyright (C) Rong Tao
include /boot/config-$(shell uname -r)

ifeq ($(CONFIG_PREEMPT),y)
PREEMPT=m
else
$(warning WARNING: CONFIG_PREEMPT is not set, these modules will cause soft lockup)
endif

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif
obj-m += loop.o
obj-m += timer_list.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
