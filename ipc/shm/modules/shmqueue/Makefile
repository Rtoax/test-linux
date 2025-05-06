MODULE_NAME = shmqueue

$(MODULE_NAME)-objs := shmq.o
obj-m := $(MODULE_NAME).o

KERNEL_DIR=/lib/modules/`uname -r`/build
MODULEDIR := $(shell pwd)


.PHONY: modules
default: modules

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
	${Q}make rmmod || true
	${Q}make rmnod || true
	${Q}make
	${Q}make mknod
	${Q}make insmod
	@echo "Test------------"
	gcc test.c -pthread -lrt -o test
	@./test
	@echo "SHMQ LOG------------"
	grep SHMQ /var/log/messages -n
	@echo "Test------------"
	@./test

clean distclean:
	@echo "clean"
	${Q}make -C $(KERNEL_DIR) M=$(MODULEDIR) clean
	${Q}rm -rf *.o *.mod.c .*.*.cmd *.ko *.out
	${Q}rm -rf .tmp_versions *.symvers *.order

