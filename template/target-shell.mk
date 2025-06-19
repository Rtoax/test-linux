# SPDX-License-Identifier: GPL-3.0
SHELL ?= bash
Q ?= @

# see TARGETS_SHELL_LOGS
%.sh.log: %.sh
	@echo -e "  SHELL  \033[1;32m$(@)\033[m"
	$(Q)${SHELL} $(<) $(ARGS_$(*)) $(SHELL_ARGS_$(<)) | tee $(@)
