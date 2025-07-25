# SPDX-License-Identifier: GPL-3.0
PYTHON ?= python
Q ?= @

# see targets-python-logs
%.py.log: %.py
	$(call log_tgt_exe,PYTHON,$(<),$(@))
	$(Q)${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<)) | tee $(@)
