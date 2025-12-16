# SPDX-License-Identifier: GPL-3.0
_TARGET_BPFTRACE = 1

include dir.mk
include sudo.mk
include bpf/bpftrace.mk

RUN_BT := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUN_BT += --verbose
endif

%.bt.log: %.bt
	$(call log_exe,BPFTRACE,$(<),$(@))
	$(Q)${SUDO} $(RUN_BT) $(@) $(BPFTRACE) $(<) $(ARGS_$(*))
