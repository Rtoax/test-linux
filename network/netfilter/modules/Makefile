include ../../../tlbuild.mk



obj-m += nf_register_net_hook.o
obj-m += xt_register_match.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
