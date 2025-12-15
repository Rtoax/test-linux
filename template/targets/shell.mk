# SPDX-License-Identifier: GPL-3.0
_TARGET_SHELL = 1

include shell.mk
include dir.mk

RUN_SHELL := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUN_SHELL += --verbose
endif

%.sh.log: %.sh
	$(call log_exe,SHELL,$(<),$(@))
	$(Q)$(RUN_SHELL) $(@) ${SHELL} $(<) $(ARGS_$(*)) $(SHELL_ARGS_$(<))
