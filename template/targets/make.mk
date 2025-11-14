# SPDX-License-Identifier: GPL-3.0
_TARGET_MAKE = 1

MAKE := make

RUN_MAKE := ${TEMPLATE_DIR}/targets/run_prog.sh

ifdef DEBUG
  RUN_MAKE += --verbose
endif

%.make.log: %.make
	$(call log_tgt_exe,MAKE,$(<),$(@))
	$(Q)$(RUN_MAKE) $(@) $(MAKE) -f $(<) $(ARGS_$(*))
