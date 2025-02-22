
obj-m += tasklet_init.o
obj-m += tasklet-template.o
obj-m += red_tasklet.o
obj-m += tasklet-bh.o
obj-m += tasklet-module1.o
obj-m += tasklet-module2.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all default: modules
install: modules_install

test:
	@echo >/dev/null

modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@
