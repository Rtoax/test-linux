include ../../tlbuild.mk



obj-m += kthread_run.o
obj-m += kthread_run-tasks.o
obj-m += multitask.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
