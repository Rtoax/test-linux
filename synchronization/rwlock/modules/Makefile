SHELL = bash
include ../../../tlbuild.mk



obj-m += rwlock_init.o
obj-m += write_lock.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
