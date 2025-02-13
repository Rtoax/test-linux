SHELL = bash
include ../../tlbuild.mk


obj-m += timer01.o
obj-m += timer02.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
