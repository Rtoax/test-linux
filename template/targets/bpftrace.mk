# SPDX-License-Identifier: GPL-3.0
#
# For bpftrace-y
#
# - BT_ARGS=
# - BT_ARGS_*=
# - BT_ENVS=
# - BT_ENVS_*=
#
ifndef _TARGET_BPFTRACE_MK
_TARGET_BPFTRACE_MK = 1

include dir.mk
include sudo.mk
include bpf/bpftrace.mk
include runprog.mk

${OUTPUT}%.bt.log: %.bt
	@$(call log_tgt,${BPFTRACE},$(@))
	$(Q)${SUDO_NOPASSWD} $(RUNPROG) ${BT_ENVS} ${BT_ENVS_${<}} --log $(@) -- $(BPFTRACE) $(<) $(BT_ARGS) $(BT_ARGS_$(<))

# $1: 1, 2, 3, ...
define add_bpftrace_target
${OUTPUT}%.bt.log.${1}: %.bt
	@$$(call log_tgt,${BPFTRACE},$$(@))
	$$(Q)$${SUDO_NOPASSWD} $$(RUNPROG) $$(BT_ENVS) $$(BT_ENVS_$$(<).${1}) --log $$(@) -- $$(BPFTRACE) $$(<) $$(BT_ARGS) $$(BT_ARGS_$$(<).${1})
endef

$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call add_bpftrace_target,${sfx})))

endif
