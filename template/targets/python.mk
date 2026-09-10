# SPDX-License-Identifier: GPL-3.0
#
# For python-y
#
ifndef _TARGET_PYTHON_MK
_TARGET_PYTHON_MK = 1

include python.mk
include dir.mk
include runprog.mk

${OUTPUT}%.py.log: %.py
	@$(call log_tgt,${PYTHON},$(@))
	@$(call __prog_stdout_color)
	$(Q)$(RUNPROG) --log $(@) -- ${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<))
	@$(call __prog_stdout_rst)

# $1: 1, 2, 3, ...
define add_python_target
${OUTPUT}%.py.log.${1}: %.py
	@$$(call log_tgt,${PYTHON},$$(@))
	@$$(call __prog_stdout_color)
	$$(Q)$$(RUNPROG) --log $$(@) -- $${PYTHON} $$(<) $$(ARGS_$$(*).${1}) $$(PY_ARGS_$$(<).${1})
	@$$(call __prog_stdout_rst)
endef

$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call add_python_target,${sfx})))

endif
