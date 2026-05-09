# SPDX-License-Identifier: GPL-3.0
#
# Input definitions:
# - PROG_ENVS_*=--env ENV=V
# - PROG_ARGS_*=
#
ifndef _TARGET_PROG_MK
_TARGET_PROG_MK = 1

include shell.mk
include dir.mk
include runprog.mk

${OUTPUT}%.prog.log: %
	$(call log_tgt,PROG,$(@))
	$(Q)$(RUNPROG) --log $(@) $(PROG_ENVS_$(<)) -- $(<) $(PROG_ARGS_$(<))

define add_prog_target
${OUTPUT}%.prog.log.${1}: %
	$$(call log_tgt,PROG,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) $$(PROG_ENVS_$$(<).${1}) -- $$(<) $$(PROG_ARGS_$$(<).${1})
endef

$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call add_prog_target,${sfx})))

endif
