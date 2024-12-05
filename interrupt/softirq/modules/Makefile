SHELL = bash


obj-m += nr_softirqs.o
obj-m += show_softirqs.o
obj-m += softirq_count.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
