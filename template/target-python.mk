# SPDX-License-Identifier: GPL-3.0
PYTHON ?= python
Q ?= @

# see TARGETS_PYTHON_LOGS
%.py.log: %.py
	$(call log_tgt_exe,PYTHON,$(<),$(@))
	$(Q)${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<)) | tee $(@)
