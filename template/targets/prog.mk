# SPDX-License-Identifier: GPL-3.0
#
# For prog-y
#
# Input definitions:
# - PROG_ENVS=--env ENV=V
# - PROG_ENVS_${prog}=--env ENV=V
# - PROG_ARGS=
# - PROG_ARGS_${prog}=
#
ifndef _TARGET_PROG_MK
_TARGET_PROG_MK = 1

include shell.mk
include dir.mk
include runprog.mk

${OUTPUT}%.prog.log: %
	@$(call log_tgt,PROG,$(@))
	@$(call __prog_stdout_color)
	$(Q)$(RUNPROG) --log $(@) $(PROG_ENVS) $(PROG_ENVS_$(<)) -- $(<) ${PROG_ARGS} $(PROG_ARGS_$(<))
	@$(call __prog_stdout_rst)

define add_prog_target
${OUTPUT}%.prog.log.${1}: %
	@$$(call log_tgt,PROG,$$(@))
	@$$(call __prog_stdout_color)
	$$(Q)$$(RUNPROG) --log $$(@) $$(PROG_ENVS) $$(PROG_ENVS_$$(<).${1}) -- $$(<) $$(PROG_ARGS) $$(PROG_ARGS_$$(<).${1})
	@$$(call __prog_stdout_rst)
endef

$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call add_prog_target,${sfx})))

endif
