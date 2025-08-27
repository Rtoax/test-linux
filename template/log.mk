# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao

ifeq (${TOPDIR},)
  $(error Not define TOPDIR)
endif

ifeq (${ANSI_BOLD},)
  $(error Not define ANSI_BOLD)
endif

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
define HOST
[$(shell hostname)]
endef
define log_tgt_obj
@printf '$(call TS) %-8s ${ANSI_BOLD}%s${ANSI_RST} -> ${ANSI_BOLD}%s${ANSI_RST}\n' "${1}" "$(2)" "$(3)"
endef
define log_tgt_exe
@printf '$(call TS) %-8s ${ANSI_BOLD}%s${ANSI_RST} -> ${ANSI_BOLD}${ANSI_GRE}%s${ANSI_RST}\n' "${1}" "$(2)" "$(3)"
endef
define log_tgt_start
@echo -e "$(call TS) [$(1)] ${ANSI_BOLD}${ANSI_GRE}$(2)${ANSI_RST} start"
endef
define log_tgt_done
@echo -e "$(call TS) [$(1)] ${ANSI_BOLD}${ANSI_YEL}$(2)${ANSI_RST} done"
endef

define log_info
printf '$(call TS) $(call HOST) $1\n' | tee --append ${LOG_FILE_INFO}
endef

define log_failed
printf '$(call TS) $(call HOST) ${ANSI_RED}$1${ANSI_RST}\n' | tee --append ${LOG_FILE_FAILED}
endef

define log_reset_files
	${Q}rm -f $(LOG_FILE_FAILED) $(LOG_FILE_INFO)
endef

define log_display_failed
	${Q}if [[ -e $(LOG_FILE_FAILED) ]]; then \
		cat $(LOG_FILE_FAILED) ; \
	fi
endef
