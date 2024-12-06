SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


obj-m	:=   ramdisk_driver.o

KBUILD_CFLAGS +=-g -O0
BASEINCLUDE ?= /lib/modules/$(shell uname -r)/build

all : 
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;
	
clean:
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) clean;


