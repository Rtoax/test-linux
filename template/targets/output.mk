# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_OUTPUT_MK
_TARGET_OUTPUT_MK = 1

include dir.mk

MKDIR ?= mkdir

ifeq ($(filter %/,$(OUTPUT)),)
  $(error OUTPUT must end with '/', now is ${OUTPUT})
endif

ifdef DEBUG
  $(info OUTPUT = ${OUTPUT})
endif

ifneq (${OUTPUT},)
${OUTPUT}:
	@$(call log_tgt,${MKDIR},$(call strip_topdir_prefix,$(shell pwd))/$(@))
	${Q}${MKDIR} -p $(@)
endif

endif
