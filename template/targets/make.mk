# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_MAKE_MK
_TARGET_MAKE_MK = 1

MAKE := make

include runprog.mk

# $1 - suffix of file: mk, mak
define make_obj
%.${1}.log: %.${1}
	$$(call log_tgt,MAKE,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) -- $$(MAKE) -f $$(<) $$(ARGS_$$(<))
endef

# $1 - suffix of file: mk, mak
# $2 - <N> number of targets
define make_obj_n
%.${1}.log.${2}: %.${1}
	$$(call log_tgt,MAKE,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) -- $$(MAKE) -f $$(<) $$(ARGS_$$(<).${2})
endef

$(eval $(call make_obj,mk))
$(eval $(call make_obj,mak))
$(foreach sfx, ${src-sfx-list}, $(eval $(call make_obj_n,mk,${sfx})))
$(foreach sfx, ${src-sfx-list}, $(eval $(call make_obj_n,mak,${sfx})))

endif
