# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_PYTHON_MK
_TARGET_PYTHON_MK = 1

include python.mk
include dir.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUNPROG += --verbose
endif

%.py.log: %.py
	$(call log_exe,PYTHON,$(<),$(@))
	$(Q)$(RUNPROG) --log $(@) -- ${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<))

endif
