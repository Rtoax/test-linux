SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



obj-m := dram.o

KDIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

default:
	gcc ./fileview.cpp -o fileview
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm fileview
	$(MAKE) -C $(KDIR) M=$(PWD) clean
