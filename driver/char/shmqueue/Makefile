SHELL = bash

#ifneq ($(KERNELRELEASE),)
MODULE_NAME = shmqueue

$(MODULE_NAME)-objs := shmq.o 
obj-m := $(MODULE_NAME).o

#else
KERNEL_DIR=/lib/modules/`uname -r`/build
MODULEDIR := $(shell pwd)


.PHONY:modules
default:modules

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
	@make rmmod
	@make rmnod
	@make 
	@make mknod
	@make insmod
	@echo "Test------------"
	gcc test.c -pthread -lrt
	@./a.out
	@echo "SHMQ LOG------------"
	grep SHMQ /var/log/messages -n 
	@echo "Test------------"
	@./a.out
	
clean distclean:
	@echo "clean"
	@make -C $(KERNEL_DIR) M=$(MODULEDIR) clean
	@rm -rf *.o *.mod.c .*.*.cmd *.ko *.out
	@rm -rf .tmp_versions *.symvers *.order
#endif

#MODULE_NAME=hellomodule

#insmod:
#	insmod $(MODULE_NAME).ko

#rmmod:
#	rmmod $(MODULE_NAME)

