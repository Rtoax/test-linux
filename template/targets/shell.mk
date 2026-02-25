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

%.sh.log: %.sh
	$(call log_exe,SHELL,$(@))
	$(Q)$(RUNPROG) --log $(@) $(SHELL_ENVS_$(<)) -- ${SHELL} $(<) $(SHELL_ARGS_$(<))

# If you want to test a script twice, add a .1 suffix to the script, for
# example: target-shell-y := a.sh a.sh.1
define sh_target
%.sh.log.${1}: %.sh
	$$(call log_exe,SHELL,$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) $$(SHELL_ENVS_$$(<).${1}) -- $${SHELL} $$(<) $$(SHELL_ARGS_$$(<).${1})
endef

$(foreach sfx, ${multi-suffix-n}, $(eval $(call sh_target,${sfx})))

endif
