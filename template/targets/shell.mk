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
	$(call log_exe,SHELL,$(<),$(@))
	$(Q)$(RUNPROG) --log $(@) $(SHELL_ENVS_$(<)) -- ${SHELL} $(<) $(SHELL_ARGS_$(<))

endif
