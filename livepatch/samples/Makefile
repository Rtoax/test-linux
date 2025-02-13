SHELL = bash
include ../../tlbuild.mk


# Copyright (C) Rong Tao
include /boot/config-$(shell uname -r)

EXTRA_CFLAGS := -Wall -g

LIVEPATCH:=

ifeq ($(CONFIG_LIVEPATCH),y)
LIVEPATCH=m
endif
obj-$(LIVEPATCH) += livepatch-callbacks-busymod.o
obj-$(LIVEPATCH) += livepatch-callbacks-demo.o
obj-$(LIVEPATCH) += livepatch-callbacks-mod.o
obj-$(LIVEPATCH) += livepatch-sample.o
obj-$(LIVEPATCH) += livepatch-sample-2nd.o
obj-$(LIVEPATCH) += livepatch-shadow-fix1.o
obj-$(LIVEPATCH) += livepatch-shadow-fix2.o
obj-$(LIVEPATCH) += livepatch-shadow-mod.o
obj-$(LIVEPATCH) += loadavg_proc_show.o

all:
	@echo "CONFIG_LIVEPATCH = $(CONFIG_LIVEPATCH)"
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
