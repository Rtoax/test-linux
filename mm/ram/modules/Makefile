SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m += totalram_pages.o

PWD := $(shell pwd)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build


default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) clean
