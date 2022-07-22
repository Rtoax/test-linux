obj-$(CONFIG_LIVEPATCH) += livepatch-callbacks-busymod.o
obj-$(CONFIG_LIVEPATCH) += livepatch-callbacks-demo.o
obj-$(CONFIG_LIVEPATCH) += livepatch-callbacks-mod.o
obj-$(CONFIG_LIVEPATCH) += livepatch-sample.o
obj-$(CONFIG_LIVEPATCH) += livepatch-shadow-fix1.o
obj-$(CONFIG_LIVEPATCH) += livepatch-shadow-fix2.o
obj-$(CONFIG_LIVEPATCH) += livepatch-shadow-mod.o
obj-$(CONFIG_LIVEPATCH) += loadavg_proc_show.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
