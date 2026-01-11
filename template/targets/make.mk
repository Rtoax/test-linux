# SPDX-License-Identifier: GPL-3.0
_TARGET_MAKE_MK = 1

MAKE := make

include dir.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUNPROG += --verbose
endif

# $1 - suffix of file: mk, mak
define make_obj
%.${1}.log: %.${1}
	$$(call log_exe,MAKE,$$(<),$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) -- $$(MAKE) -f $$(<) $$(ARGS_$$(*))
endef
$(eval $(call make_obj,mk))
$(eval $(call make_obj,mak))
