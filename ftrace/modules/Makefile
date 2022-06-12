obj-m += ftrace-direct.o
obj-m += ftrace-direct-modify.o
obj-m += ftrace-direct-too.o
#obj-m += sample-trace-array.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
