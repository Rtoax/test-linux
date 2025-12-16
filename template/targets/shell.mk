# SPDX-License-Identifier: GPL-3.0
#
# Input definitions:
# - SHELL_ARGS_*=
#
_TARGET_SHELL = 1

include shell.mk
include dir.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUNPROG += --verbose
endif

%.sh.log: %.sh
	$(call log_exe,SHELL,$(<),$(@))
	$(Q)$(RUNPROG) --log $(@) -- ${SHELL} $(<) $(SHELL_ARGS_$(<))
