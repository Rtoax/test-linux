SHELL = bash


obj-m += zone.o
obj-m += first_online_node.o
obj-m += first_memory_node.o
obj-m += for_each_node_state.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
