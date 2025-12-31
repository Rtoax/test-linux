# SPDX-License-Identifier: GPL-3.0
_TARGET_BPFTRACE_MK = 1

include dir.mk
include sudo.mk
include bpf/bpftrace.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUNPROG += --verbose
endif

%.bt.log: %.bt
	$(call log_exe,BPFTRACE,$(<),$(@))
	$(Q)${SUDO} $(RUNPROG) --log $(@) -- $(BPFTRACE) $(<) $(ARGS_$(*))
