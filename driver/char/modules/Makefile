SHELL = bash
include ../../../tlbuild.mk


obj-m += hello.o
obj-m += chardev0.o
obj-m += chardev1.o
obj-m += chardev2.o
obj-m += chardev3.o
obj-m += chardev4.o

KERNEL_DIR=/lib/modules/`uname -r`/build
MODULE_DIR := $(shell pwd)

all:
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules
clean:
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) clean
	rm -f \
		hello_user \
		chardev1_user \
		chardev2_user \
		chardev3_user \
		chardev4_user
test:
	gcc ./hello_user.c -o hello_user
	gcc ./chardev1_usertest.c -o chardev1_user
	gcc ./chardev2_usertest.c -o chardev2_user
	gcc ./chardev3_usertest.c -o chardev3_user
	gcc ./chardev4_usertest.c -o chardev4_user
