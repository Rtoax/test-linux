
obj-m += kprobe_icmp_echo.o
obj-m += kprobe_example.o
obj-m += kretprobe_example.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
