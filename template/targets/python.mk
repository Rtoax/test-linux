# SPDX-License-Identifier: GPL-3.0
_TARGET_PYTHON = 1

PYTHON ?= python

RUN_PYTHON := ${TEMPLATE_DIR}/targets/run_prog.sh

ifdef DEBUG
  RUN_PYTHON += --verbose
endif

# see target-python-logs
%.py.log: %.py
	$(call log_tgt_exe,PYTHON,$(<),$(@))
	$(Q)$(RUN_PYTHON) $(@) ${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<))
