# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_PYTHON_MK
_TARGET_PYTHON_MK = 1

include python.mk
include dir.mk
include runprog.mk

%.py.log: %.py
	$(call log_exe,PYTHON,$(<),$(@))
	$(Q)$(RUNPROG) --log $(@) -- ${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<))

# $1: 1, 2, 3, ...
define py_target
%.py.log.${1}: %.py
	$$(call log_exe,PYTHON,$$(<),$$(@))
	$$(Q)$$(RUNPROG) --log $$(@) -- $${PYTHON} $$(<) $$(ARGS_$$(*).${1}) $$(PY_ARGS_$$(<).${1})
endef

$(foreach sfx, 1 2 3 4 5 6 7 8 9, $(eval $(call py_target,${sfx})))

endif
