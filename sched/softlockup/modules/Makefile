include /boot/config-$(shell uname -r)

ifeq ($(CONFIG_PREEMPT),y)
  PREEMPT=m
else
  $(warning WARNING: CONFIG_PREEMPT is not set, these modules will cause soft lockup)
endif

obj-m += loop.o
obj-m += timer_list.o
obj-m += rcu_stall.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

build:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	${Q}make -C ${KERNELDIR} M=$(PWD) clean
