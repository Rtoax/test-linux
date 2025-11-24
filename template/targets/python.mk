# SPDX-License-Identifier: GPL-3.0
_TARGET_PYTHON = 1

PYTHON := $(shell which python 2>/dev/null || true)
ifeq (${PYTHON},)
  PYTHON := $(shell which python3 2>/dev/null || true)
endif
ifeq (${PYTHON},)
  $(error "Not found python or python3")
endif

include dir.mk

RUN_PYTHON := ${TOPDIR}/template/targets/run_prog.sh

ifdef DEBUG
  RUN_PYTHON += --verbose
  $(info PYTHON = ${PYTHON})
endif

%.py.log: %.py
	$(call log_exe,PYTHON,$(<),$(@))
	$(Q)$(RUN_PYTHON) $(@) ${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<))
