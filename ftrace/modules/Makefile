
ifeq ($(shell uname -m),x86_64)
obj-m += ftrace-direct.o
obj-m += ftrace-direct-modify.o
obj-m += ftrace-direct-too.o
endif
#obj-m += sample-trace-array.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
