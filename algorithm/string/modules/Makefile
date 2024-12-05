SHELL = bash


obj-m += test_hexdump.o
obj-m += test_kstrtox.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
