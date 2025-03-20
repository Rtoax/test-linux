
obj-m += super_block.o
obj-m += register_filesystem.o
obj-m += d_path.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

all:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	${Q}make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
