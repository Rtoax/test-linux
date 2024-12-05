SHELL = bash

obj-m += key-handler-kernel.o
ccflags-y := -std=gnu99 -Wno-declaration-after-statement

.PHONY : clean

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(CURDIR) modules
	@make -f Makefile.user
	sudo insmod key-handler-kernel.ko
clean:
	sudo rm -f /dev/key-handler
	@make -C /lib/modules/$(shell uname -r)/build M=$(CURDIR) clean
	@make -f Makefile.user clean
	sudo rmmod key-handler-kernel
