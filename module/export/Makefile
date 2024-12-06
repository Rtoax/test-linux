SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m += export-syms.o
obj-m += extern-syms.o

KERNEL_DIR = /lib/modules/`uname -r`/build
MODULE_DIR := $(shell pwd)

modules:
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules

clean:
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) clean
