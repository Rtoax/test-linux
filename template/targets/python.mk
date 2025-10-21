# SPDX-License-Identifier: GPL-3.0
_TARGET_PYTHON = 1

PYTHON ?= python
Q ?= @

# see target-python-logs
%.py.log: %.py
	$(call log_tgt_exe,PYTHON,$(<),$(@))
	$(Q)${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<)) | tee $(@)
