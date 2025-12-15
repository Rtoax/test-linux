# SPDX-License-Identifier: GPL-3.0
_TARGET_MAKE = 1

MAKE := make

include dir.mk

RUN_MAKE := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUN_MAKE += --verbose
endif

%.make.log: %.make
	$(call log_exe,MAKE,$(<),$(@))
	$(Q)$(RUN_MAKE) $(@) $(MAKE) -f $(<) $(ARGS_$(*))
