obj-m += key-handler-kernel.o
ccflags-y := -std=gnu99 -Wno-declaration-after-statement

.PHONY : clean

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(CURDIR) modules
	${Q}make -f Makefile.user
	sudo insmod key-handler-kernel.ko
clean:
	sudo rm -f /dev/key-handler
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(CURDIR) clean
	${Q}make -f Makefile.user clean
	sudo rmmod key-handler-kernel
