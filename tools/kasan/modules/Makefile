obj-m += vmalloc-out-of-bounds.o
obj-m += slab-out-of-bounds.o
obj-m += global-out-of-bounds.o
obj-m += use-after-free.o
obj-m += slab.o
obj-m += stack.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
