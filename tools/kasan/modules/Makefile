
obj-m += vmalloc-out-of-bounds.o
obj-m += slab-out-of-bounds.o
obj-m += slab.o
obj-m += global.o
obj-m += stack.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
