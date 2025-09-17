# SPDX-License-Identifier: GPL-3.0
_TARGET_OUTPUT = 1

MKDIR ?= mkdir

ifeq ($(filter %/,$(OUTPUT)),)
  $(error OUTPUT must end with '/', now is ${OUTPUT})
endif

ifdef DEBUG
  $(info OUTPUT = ${OUTPUT})
endif

${OUTPUT}:
	$(call log_tgt_exe,MKDIR,$(<),$(@))
	${Q}${MKDIR} -p $(@)
