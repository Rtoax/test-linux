SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m += workqueue-template.o
obj-m += workqueue1.o
obj-m += workqueue2.o
obj-m += workqueue3-hd.o
obj-m += workqueue4.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
