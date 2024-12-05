SHELL = bash


obj-m += cn_test.o

TARGETS := ucon

all: ${TARGETS}
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@sudo insmod cn_test.ko
	@sudo ./ucon

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f ${TARGETS}
