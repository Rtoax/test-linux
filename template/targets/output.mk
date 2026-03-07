# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_OUTPUT_MK
export _TARGET_OUTPUT_MK = 1

MKDIR ?= mkdir

ifeq ($(filter %/,$(OUTPUT)),)
  $(error OUTPUT must end with '/', now is ${OUTPUT})
endif

ifdef DEBUG
  $(info OUTPUT = ${OUTPUT})
endif

${OUTPUT}:
	$(call log_tgt,MKDIR,$(@))
	${Q}${MKDIR} -p $(@)

endif
