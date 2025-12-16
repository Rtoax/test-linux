# SPDX-License-Identifier: GPL-3.0
_TARGET_MAKE = 1

MAKE := make

include dir.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUNPROG += --verbose
endif

%.make.log: %.make
	$(call log_exe,MAKE,$(<),$(@))
	$(Q)$(RUNPROG) --log $(@) -- $(MAKE) -f $(<) $(ARGS_$(*))
