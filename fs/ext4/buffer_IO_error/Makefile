SHELL = bash

# Copyright (C) Rong Tao
include /boot/config-$(shell uname -r)

LIVEPATCH:=

ifeq ($(CONFIG_LIVEPATCH),y)
LIVEPATCH=m
endif
obj-$(LIVEPATCH) += buffer_IO_error.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
