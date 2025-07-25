# SPDX-License-Identifier: GPL-3.0
SHELL ?= bash
Q ?= @

# see targets-shell-logs
%.sh.log: %.sh
	$(call log_tgt_exe,SHELL,$(<),$(@))
	$(Q)${SHELL} $(<) $(ARGS_$(*)) $(SHELL_ARGS_$(<)) | tee $(@)
