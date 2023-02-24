obj-m += vhost_test.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C ${KERNELDIR} M=$(PWD) modules
clean:
	make -C ${KERNELDIR} M=$(PWD) clean

sync:
	cp /home/rongtao/Git/linux/drivers/vhost/test.c .
	cp /home/rongtao/Git/linux/drivers/vhost/test.h .
	cp /home/rongtao/Git/linux/drivers/vhost/vhost.h .
