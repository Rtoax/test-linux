include ../../../tlbuild.mk



obj-m += slab_def.o
obj-m += kmem_cache_create.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
