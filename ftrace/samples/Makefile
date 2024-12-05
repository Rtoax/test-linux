SHELL = bash


ifeq ($(shell uname -m),x86_64)
obj-m += ftrace-direct.o
obj-m += ftrace-direct-too.o
obj-m += ftrace-direct-modify.o
endif
obj-m += ftrace-direct-multi.o
obj-m += ftrace-direct-multi-modify.o
obj-m += ftrace-ops.o
#obj-m += sample-trace-array.o

all:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
