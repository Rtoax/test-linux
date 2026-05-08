# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
#
# Functions:
# - log_obj()
# - log_tgt()
# - log_info()
# - log_warn()
# - log_fail()
# - log_success()
# - log_reset()
# - log_display_failed()
#
ifndef _LOG_MK
_LOG_MK = 1

include dir.mk
include ansi.mk
include file.mk
include shell.mk

LOG_FILE_INFO := $(TOPDIR)/info.log
LOG_FILE_FAILED := $(TOPDIR)/failed.log

# Timestamp
define LOG_PFX
$(if ${DEBUG},[$(shell date '+%Y/%m/%d %H:%M:%S')])
endef

define log_obj
@printf "$(call LOG_PFX) %-8s $(call bold,%s)\n" "${1}" "$(2)"
endef

define log_tgt
@printf "$(call LOG_PFX) %-8s $(call bgreen,%s)\n" "${1}" "$(2)"
endef

define log_info
printf "$(call LOG_PFX) $1\n" | tee --append ${LOG_FILE_INFO}
endef

define log_fail
printf "$(call LOG_PFX) $(call red,$1)\n" | tee --append ${LOG_FILE_FAILED}
endef

define log_warn
printf "$(call LOG_PFX) $(call cyan,$1)\n" | tee --append ${LOG_FILE_INFO}
endef

define log_success
printf "$(call LOG_PFX) $(call green,$1)\n" | tee --append ${LOG_FILE_INFO}
endef

define log_reset
	${Q}$(call reset_file,${LOG_FILE_FAILED}); \
	$(call reset_file,${LOG_FILE_INFO})
endef

define log_display_failed
	${Q}if [[ -e $(LOG_FILE_FAILED) ]]; then \
		cat $(LOG_FILE_FAILED) ; \
	fi
endef

ifdef DEBUG
  $(info LOG_FILE_INFO = ${LOG_FILE_INFO})
  $(info LOG_FILE_FAILED = ${LOG_FILE_FAILED})
endif

export LOG_FILE_INFO LOG_FILE_FAILED

endif
