SHELL = bash

MODULE_NAME = shmqueue

$(MODULE_NAME)-objs := shmq.o
obj-m := $(MODULE_NAME).o

KERNEL_DIR=/lib/modules/`uname -r`/build
MODULEDIR := $(shell pwd)


.PHONY: modules
default: modules

modules:
	@make -C $(KERNEL_DIR) M=$(MODULEDIR) modules

insmod:
	@echo "insert load module"
	@insmod $(MODULE_NAME).ko

mknod:
	@echo "make node "
	@mknod /dev/$(MODULE_NAME) c 231 0

rmmod:
	@echo "remove module"
	@rmmod $(MODULE_NAME)

rmnod:
	@echo "remove node"
	@rm /dev/$(MODULE_NAME)

test:
	@make rmmod || true
	@make rmnod || true
	@make
	@make mknod
	@make insmod
	@echo "Test------------"
	gcc test.c -pthread -lrt -o test
	@./test
	@echo "SHMQ LOG------------"
	grep SHMQ /var/log/messages -n
	@echo "Test------------"
	@./test

clean distclean:
	@echo "clean"
	@make -C $(KERNEL_DIR) M=$(MODULEDIR) clean
	@rm -rf *.o *.mod.c .*.*.cmd *.ko *.out
	@rm -rf .tmp_versions *.symvers *.order

