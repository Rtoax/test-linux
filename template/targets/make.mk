# SPDX-License-Identifier: GPL-3.0
_TARGET_MAKE = 1

MAKE := make

MAKE_SH := ${TEMPLATE_DIR}/targets/run_prog.sh

ifdef DEBUG
  MAKE_SH += --verbose
endif

MAKE_SH += make

%.mk.log: %.mk
	$(call log_tgt_exe,MAKE,$(<),$(@))
	$(Q)$(MAKE_SH) $(@) -f $(<) $(ARGS_$(*))
