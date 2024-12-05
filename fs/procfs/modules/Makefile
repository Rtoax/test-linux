SHELL = bash

obj-m += myproc.o
obj-m += baseproc.o
obj-m += cmdline.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
