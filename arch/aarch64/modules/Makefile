target-y += currentel_user
obj-m += currentel.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all: ${target-y}
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
	${Q}rm -f ${target-y} *.o *.d
