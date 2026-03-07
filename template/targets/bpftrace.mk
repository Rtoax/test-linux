# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_BPFTRACE_MK
export _TARGET_BPFTRACE_MK = 1

include dir.mk
include sudo.mk
include bpf/bpftrace.mk
include runprog.mk

%.bt.log: %.bt
	$(call log_tgt,BPFTRACE,$(@))
	$(Q)${SUDO} $(RUNPROG) --log $(@) -- $(BPFTRACE) $(<) $(ARGS_$(*))

# $1: 1, 2, 3, ...
define bt_target
%.bt.log.${1}: %.bt
	$$(call log_tgt,BPFTRACE,$$(@))
	$$(Q)$${SUDO} $$(RUNPROG) --log $$(@) -- $$(BPFTRACE) $$(<) $$(ARGS_$$(<).${1})
endef

$(foreach sfx, ${SRC_SFX_LIST}, $(eval $(call bt_target,${sfx})))

endif
