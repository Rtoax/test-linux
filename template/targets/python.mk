# SPDX-License-Identifier: GPL-3.0
_TARGET_PYTHON = 1

PYTHON ?= python

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

RUN_PYTHON := ${TOPDIR}/template/targets/run_prog.sh

ifdef DEBUG
  RUN_PYTHON += --verbose
endif

%.py.log: %.py
	$(call log_exe,PYTHON,$(<),$(@))
	$(Q)$(RUN_PYTHON) $(@) ${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<))
