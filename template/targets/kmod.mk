# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_KMOD_MK
_TARGET_KMOD_MK = 1

# TODO: move to kcompile.mk
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
MODULE_DIR := ${CURDIR}

.PHONY: kmods-build
kmods-build: ${kmod-build-y}
	$(call log_tgt,KMOD BUILD,$(@))
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules

.PHONY: kmods-clean
kmods-clean:
	$(call log_tgt,KMOD CLEAN,$(@))
	${Q}make -C $(KERNEL_DIR) M=$(MODULE_DIR) clean

endif
