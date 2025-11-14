# SPDX-License-Identifier: GPL-3.0
_TARGET_MAKE = 1

MAKE := make

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

RUN_MAKE := ${TOPDIR}/template/targets/run_prog.sh

ifdef DEBUG
  RUN_MAKE += --verbose
endif

%.make.log: %.make
	$(call log_tgt_exe,MAKE,$(<),$(@))
	$(Q)$(RUN_MAKE) $(@) $(MAKE) -f $(<) $(ARGS_$(*))
