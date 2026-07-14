# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
#
# Functions:
# - log_obj()
# - log_tgt()
# - log_info()
# - log_info_mk()
# - log_warn()
# - log_warn_mk()
# - log_fail()
# - log_fail_mk()
# - log_success()
# - log_success_mk()
# - log_reset()
# - log_display_failed()
#
ifndef _LOG_MK
_LOG_MK = 1

include dir.mk
include ansi.mk
include file.mk
include shell.mk
include string.mk

LOG_FILE_INFO := $(TOPDIR)/info.log
LOG_FILE_FAILED := $(TOPDIR)/failed.log
# see scripts/runprog.sh
LOG_FILE_RUNPROG := $(TOPDIR)/runprog.cmd.log
# see scripts/make_tl.sh
LOG_MAKE_TL := ${TOPDIR}/make.log

# Timestamp
define LOG_TS
[$(shell date '+%Y/%m/%d %H:%M:%S')]
endef
define LOG_PFX
$(if ${DEBUG},$(call LOG_TS))
endef

define log_obj
printf "$(call LOG_PFX) %-16s $(call bold,%s)\n" "$(call toupper_shell,$(notdir ${1}))" "$(2)"
endef

define log_tgt
printf "$(call LOG_PFX) %-16s $(call bgreen,%s)\n" "$(call toupper_shell,$(notdir ${1}))" "$(2)"
endef

define log_info
printf "$(call LOG_PFX) $1\n" | tee --append ${LOG_FILE_INFO}
endef
define log_info_mk
$(info $(shell $(call log_info,${1})))
endef

define log_fail
printf "$(call LOG_TS) $(call red,$1)\n" | tee --append ${LOG_FILE_FAILED}
endef
define log_fail_mk
$(info $(shell $(call log_fail,${1})))
endef

define log_warn
printf "$(call LOG_PFX) $(call red,$1)\n" | tee --append ${LOG_FILE_INFO}
endef
define log_warn_mk
$(info $(shell $(call log_warn,${1})))
endef

define log_success
printf "$(call LOG_PFX) $(call green,$1)\n" | tee --append ${LOG_FILE_INFO}
endef
define log_success_mk
$(info $(shell $(call log_success,${1})))
endef

define log_reset
	${Q}$(call reset_file,${LOG_FILE_FAILED}); \
	$(call reset_file,${LOG_FILE_INFO}); \
	$(call reset_file,${LOG_FILE_RUNPROG}); \
	$(call reset_file,${LOG_MAKE_TL})
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

ifdef TEST
  $(foreach func, log_obj log_tgt log_info log_fail log_warn log_success, \
    $(info $(shell $(call ${func},TEST ${func},ARG1,ARG2))) \
  )
  $(foreach func, log_info_mk log_warn_mk log_fail_mk log_success_mk, \
    $(call ${func},TEST ${func}) \
  )
endif

endif
