obj-m += nothing.o
obj-m += reloc.o

KERNEL_DIR=/lib/modules/`uname -r`/build
MODULE_DIR := $(shell pwd)

modules:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules

clean:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) clean
