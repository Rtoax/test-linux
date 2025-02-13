SHELL = bash
include ../../../tlbuild.mk



obj-m += zone.o
obj-m += first_online_node.o
obj-m += first_memory_node.o
obj-m += for_each_node_state.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
