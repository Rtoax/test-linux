# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_MAKE_MK
_TARGET_MAKE_MK = 1

MAKE := make

include runprog.mk

# $1 - suffix of file: mk, mak
define make_obj
%.${1}.log: %.${1}
	$$(call log_exe,MAKE,$$(<),$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) -- $$(MAKE) -f $$(<) $$(ARGS_$$(*))
endef
$(eval $(call make_obj,mk))
$(eval $(call make_obj,mak))

endif
