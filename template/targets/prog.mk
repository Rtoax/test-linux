# SPDX-License-Identifier: GPL-3.0
#
# Input definitions:
#
ifndef _TARGET_PROG_MK
_TARGET_PROG_MK = 1

include shell.mk
include dir.mk
include runprog.mk

${OUTPUT}%.prog.log: %
	$(call log_tgt,PROG,$(@))
	$(Q)$(RUNPROG) --log $(@) $(PROG_ENVS_$(<)) -- $(<) $(PROG_ARGS_$(<))

# If you want to test a script twice, add a .1 suffix to the script, for
# example: target-prog-y := a.prog a.prog.1
define prog_target
${OUTPUT}%.prog.log.${1}: %
	$$(call log_tgt,PROG,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) $$(PROG_ENVS_$$(<).${1}) -- $$(<) $$(PROG_ARGS_$$(<).${1})
endef

$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call prog_target,${sfx})))

endif
