obj-m += cn_test.o

targets := ucon

all: ${targets}
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@sudo insmod cn_test.ko
	@sudo ./ucon

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	@rm -f ${targets}
