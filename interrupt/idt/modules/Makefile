SHELL = bash

ifeq ($(shell uname -m),x86_64)
obj-m += proc-idt.o
endif
ifeq ($(shell uname -m),aarch64)
endif

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
