# SPDX-License-Identifier: GPL-3.0
_TARGET_SHELL = 1

SHELL ?= bash
Q ?= @

# see target-shell-logs
%.sh.log: %.sh
	$(call log_tgt_exe,SHELL,$(<),$(@))
	$(Q)${SHELL} $(<) $(ARGS_$(*)) $(SHELL_ARGS_$(<)) | tee $(@)
