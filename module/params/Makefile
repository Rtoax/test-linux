SHELL = bash
include ../../tlbuild.mk


obj-m += array.o
obj-m += charp.o
obj-m += int.o
obj-m += params-test0.o
obj-m += params-test1.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
