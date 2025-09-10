# SPDX-License-Identifier: GPL-3.0
_TARGET_MAKE = 1

MAKE := make

%.mk.log: %.mk
	$(call log_tgt_exe,MAKE,$(<),$(@))
	$(Q)$(MAKE) -f $(<) $(ARGS_$(*)) | tee $(@)
