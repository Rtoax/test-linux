SHELL = bash

obj-m += for_each_mem_pfn_range.o
obj-m += numa_node_id.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
