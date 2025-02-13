SHELL = bash
include ../../../tlbuild.mk



#obj-m += clocksource_resigter_hz.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
