SHELL = bash


obj-m += hash_64.o
obj-m += hash_long.o
obj-m += hash_ptr.o
obj-m += test_hash.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
