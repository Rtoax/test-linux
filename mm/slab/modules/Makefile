SHELL = bash


obj-m += slab_def.o
obj-m += kmem_cache_create.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
