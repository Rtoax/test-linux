SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



obj-m += register_sysctl.o
obj-m += register_sysctl_paths.o
obj-m += register_sysctl_table.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

all:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
