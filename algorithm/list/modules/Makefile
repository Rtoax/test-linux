SHELL = bash

obj-m += list_static.o
obj-m += list_dynamic.o
obj-m += list_rcu.o
obj-m += list_rcu_example.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
