# SPDX-License-Identifier: GPL-3.0
#
# Input definitions:
# - SHELL_ENVS_*=--env ENV=V
# - SHELL_ARGS_*=
#
ifndef _TARGET_SHELL_MK
_TARGET_SHELL_MK = 1

include shell.mk
include dir.mk
include runprog.mk

${OUTPUT}%.sh.log: %.sh
	$(call log_tgt,SHELL,$(@))
	$(Q)$(RUNPROG) --log $(@) $(SHELL_ENVS_$(<)) -- ${SHELL} $(<) $(SHELL_ARGS_$(<))

# If you want to test a script twice, add a .1 suffix to the script, for
# example: target-shell-y := a.sh a.sh.1
define add_shell_target
${OUTPUT}%.sh.log.${1}: %.sh
	$$(call log_tgt,SHELL,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) $$(SHELL_ENVS_$$(<).${1}) -- $${SHELL} $$(<) $$(SHELL_ARGS_$$(<).${1})
endef

$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call add_shell_target,${sfx})))

endif
