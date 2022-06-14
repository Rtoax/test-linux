
obj-m += kthread.o
obj-m += patchkthread.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
