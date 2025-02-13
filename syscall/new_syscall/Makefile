SHELL = bash
include ../../tlbuild.mk


obj-m += my_audit.o sys-define.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
