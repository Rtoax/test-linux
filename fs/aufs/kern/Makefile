SHELL = bash
include ../../../tlbuild.mk


ifneq ($(KERNELRELEASE),)
obj-m := aufs.o
aufs-objs := super.o inode.o dir.o file.o
CFLAGS_super.o := -DDEBUG
CFLAGS_inode.o := -DDEBUG
CFLAGS_dir.o := -DDEBUG
CFLAGS_file.o := -DDEBUG
else
all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
endif
