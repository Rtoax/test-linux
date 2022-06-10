obj-m += create-test1.o

KERNELROOT=/lib/modules/`uname -r`/build

all:
	make -C $(KERNELROOT) M=$(PWD) modules
clean:
	make -C $(KERNELROOT) M=$(PWD) clean
