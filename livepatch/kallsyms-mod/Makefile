include ../../tlbuild.mk


# Copyright (C) Rong Tao
include /boot/config-$(shell uname -r)

LIVEPATCH:=

ifeq ($(CONFIG_LIVEPATCH),y)
LIVEPATCH=m
endif

obj-$(LIVEPATCH) += kallsyms_example.o
kallsyms_example-objs := main.o kallsyms.o

MCFLAGS += -g
ccflags-y += ${MCFLAGS}
CC += ${MCFLAGS}

KDIR := /lib/modules/$(shell uname -r)/build

all:
	${Q}make -C $(KDIR) M=$(PWD) modules


test:
	@echo >/dev/null

clean:
	${Q}make -C $(KDIR) M=$(PWD) clean
