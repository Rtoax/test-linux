# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_KMOD_MK
_TARGET_KMOD_MK = 1

include kcompile.mk

.PHONY: kmods-build
kmods-build: ${kmod-build-y}
	$(call log_tgt,KMOD BUILD,$(@))
	${Q}make -C $(KDIR) M=$(MDIR) modules

.PHONY: kmods-clean
kmods-clean:
	$(call log_tgt,KMOD CLEAN,$(@))
	${Q}make -C $(KDIR) M=$(MDIR) clean

endif
