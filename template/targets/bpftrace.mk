# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_BPFTRACE_MK
_TARGET_BPFTRACE_MK = 1

include dir.mk
include sudo.mk
include bpf/bpftrace.mk
include runprog.mk

%.bt.log: %.bt
	$(call log_exe,BPFTRACE,$(<),$(@))
	$(Q)${SUDO} $(RUNPROG) --log $(@) -- $(BPFTRACE) $(<) $(ARGS_$(*))

endif
