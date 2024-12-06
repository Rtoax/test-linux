SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


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
	${Q}make -C $(KERNEL_DIR) M=$(MODULEDIR) modules

insmod:
	@echo "insert load module"
	@insmod $(MODULE_NAME).ko

mknod:
	@echo "make node "
	@mknod /dev/$(MODULE_NAME) c 231 0

rmmod:
	@echo "remove module"
	${Q}rmmod $(MODULE_NAME)

rmnod:
	@echo "remove node"
	${Q}rm /dev/$(MODULE_NAME)

test:
	${Q}make rmmod
	${Q}make rmnod
	${Q}make 
	${Q}make mknod
	${Q}make insmod
	@echo "Test------------"
	gcc test.c -pthread -lrt
	@./a.out
	@echo "SHMQ LOG------------"
	grep SHMQ /var/log/messages -n 
	@echo "Test------------"
	@./a.out
	
clean distclean:
	@echo "clean"
	${Q}make -C $(KERNEL_DIR) M=$(MODULEDIR) clean
	${Q}rm -rf *.o *.mod.c .*.*.cmd *.ko *.out
	${Q}rm -rf .tmp_versions *.symvers *.order
#endif

#MODULE_NAME=hellomodule

#insmod:
#	insmod $(MODULE_NAME).ko

#rmmod:
#	rmmod $(MODULE_NAME)

