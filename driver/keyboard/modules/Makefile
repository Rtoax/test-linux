SHELL = bash

obj-m += register_keyboard_notifier.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
