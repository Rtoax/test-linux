
# KERNELVERSION is defined in kernel's top-level Makefile, but empty here.
$(info KERNELVERSION=${KERNELVERSION})

obj-m += linux_banner.o
obj-m += KERNEL_VERSION.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
