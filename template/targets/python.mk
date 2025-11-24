# SPDX-License-Identifier: GPL-3.0
_TARGET_PYTHON = 1

include python.mk
include dir.mk

RUN_PYTHON := ${TOPDIR}/template/targets/run_prog.sh

ifdef DEBUG
  RUN_PYTHON += --verbose
endif

%.py.log: %.py
	$(call log_exe,PYTHON,$(<),$(@))
	$(Q)$(RUN_PYTHON) $(@) ${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<))
