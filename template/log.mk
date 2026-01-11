# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
_LOG_MK = 1

include shell.mk
include dir.mk
include ansi.mk

LOG_FILE_INFO := $(TOPDIR)/info.log
LOG_FILE_FAILED := $(TOPDIR)/failed.log

ifdef DEBUG
  $(info LOG_FILE_INFO = ${LOG_FILE_INFO})
  $(info LOG_FILE_FAILED = ${LOG_FILE_FAILED})
endif

# Timestamp
define TS
[$(shell date '+%H:%M:%S')]
endef
define log_obj
@printf '$(call TS) %-8s $(call bold,%s) -> $(call bold,%s)\n' "${1}" "$(2)" "$(3)"
endef
define log_exe
@printf '$(call TS) %-8s $(call bold,%s) -> $(call bgreen,%s)\n' "${1}" "$(2)" "$(3)"
endef
define log_start
@echo -e "$(call TS) [$(1)] $(call bgreen,$(2)) start"
endef
define log_end
@echo -e "$(call TS) [$(1)] $(call byellow,$(2)) done"
endef
define log_tgt
@printf '$(call TS) %-8s $(call bold,%s)\n' "${1}" "$(2)"
endef

define log_info
printf '$(call TS) $1\n' | tee --append ${LOG_FILE_INFO}
endef

define log_failed
printf '$(call TS) $(call red,$1)\n' | tee --append ${LOG_FILE_FAILED}
endef
define log_success
printf '$(call TS) $(call green,$1)\n' | tee --append ${LOG_FILE_INFO}
endef

define log_reset_files
	${Q}function ___rename_log() { \
		if [[ -e $${1} ]]; then \
			if [[ -e $${1}.old ]]; then \
				___rename_log $${1}.old; \
			fi; \
			mv $${1} $${1}.old; \
		fi; \
	}; \
	___rename_log $(LOG_FILE_FAILED); \
	___rename_log $(LOG_FILE_INFO)
endef

define log_display_failed
	${Q}if [[ -e $(LOG_FILE_FAILED) ]]; then \
		cat $(LOG_FILE_FAILED) ; \
	fi
endef
