# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_MAKE_MK
_TARGET_MAKE_MK = 1

include make.mk
include runprog.mk

# $1 - suffix of file: mk, mak
define add_make_target
${OUTPUT}%.${1}.log: %.${1}
	$$(call log_tgt,MAKE,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) -- $$(MAKE) -f $$(<) $$(ARGS_$$(<))
endef

# $1 - suffix of file: mk, mak
# $2 - <N> number of targets
define add_make_target_n
${OUTPUT}%.${1}.log.${2}: %.${1}
	$$(call log_tgt,MAKE,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) -- $$(MAKE) -f $$(<) $$(ARGS_$$(<).${2})
endef

$(eval $(call add_make_target,mk))
$(eval $(call add_make_target,mak))
$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call add_make_target_n,mk,${sfx})))
$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call add_make_target_n,mak,${sfx})))

endif
