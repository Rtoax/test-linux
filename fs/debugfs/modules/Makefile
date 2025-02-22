
obj-m += create-test1.o

KERNELROOT=/lib/modules/`uname -r`/build

all:
	${Q}make -C $(KERNELROOT) M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	${Q}make -C $(KERNELROOT) M=$(PWD) clean
