# SPDX-License-Identifier: GPL-3.0
_TARGET_SHELL = 1

SHELL ?= bash
Q ?= @

RUN_SHELL := ${TEMPLATE_DIR}/targets/run_prog.sh

ifdef DEBUG
  RUN_SHELL += --verbose
endif

RUN_SHELL += ${SHELL}

# see target-shell-logs
%.sh.log: %.sh
	$(call log_tgt_exe,SHELL,$(<),$(@))
	$(Q)$(RUN_SHELL) $(@) $(<) $(ARGS_$(*)) $(SHELL_ARGS_$(<))
