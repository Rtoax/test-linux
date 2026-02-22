# Copyright (C) Rong Tao
include /boot/config-$(shell uname -r)

LIVEPATCH:=

ifeq ($(CONFIG_LIVEPATCH),y)
LIVEPATCH=m
endif

obj-$(LIVEPATCH) += estimation_timer.o
obj-$(LIVEPATCH) += test_klp_atomic_replace.o
obj-$(LIVEPATCH) += test_klp_callbacks_busy.o
obj-$(LIVEPATCH) += test_klp_callbacks_demo2.o
obj-$(LIVEPATCH) += test_klp_callbacks_demo.o
obj-$(LIVEPATCH) += test_klp_callbacks_mod.o
obj-$(LIVEPATCH) += test_klp_livepatch.o
obj-$(LIVEPATCH) += test_klp_shadow_vars.o
obj-$(LIVEPATCH) += test_klp_state2.o
obj-$(LIVEPATCH) += test_klp_state3.o
obj-$(LIVEPATCH) += test_klp_state.o
#obj-$(LIVEPATCH) += test_klp_sysvec_apic_timer_interrupt.o
#obj-$(LIVEPATCH) += test_klp_lapic_cal_handler.o

build:
		${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
		${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
