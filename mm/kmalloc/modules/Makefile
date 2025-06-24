EXTRA_CFLAGS := -g
EXTRA_CFLAGS += -DTEST_KMALLOC=1

obj-m += kmalloc.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
