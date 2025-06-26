# SPDX-License-Identifier: GPL-3.0
MKDIR ?= mkdir

${OUTPUT}:
	$(call log_tgt_exe,MKDIR,$(<),$(@))
	${Q}${MKDIR} -p $(@)
