
obj-m += trace_irqoff.o
obj-m += trigger_irqoff.o

KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install:
	insmod trace_irqoff.ko

remove:
	rmmod trace_irqoff
