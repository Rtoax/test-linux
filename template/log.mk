# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao

ifeq (${TOPDIR},)
  $(error Not define TOPDIR)
endif

ifeq (${ANSI_BOLD},)
  $(error Not define ANSI_BOLD)
endif

FILE_LOG_INFO := $(TOPDIR)/info.log
FILE_LOG_FAILED := $(TOPDIR)/failed.log
export FILE_LOG_INFO FILE_LOG_FAILED

define timestamp
[$(shell date '+%H:%M:%S')]
endef
define log_tgt_obj
@printf '$(call timestamp) %-8s ${ANSI_BOLD}%s${ANSI_RST} -> ${ANSI_BOLD}%s${ANSI_RST}\n' "${1}" "$(2)" "$(3)"
endef
define log_tgt_exe
@printf '$(call timestamp) %-8s ${ANSI_BOLD}%s${ANSI_RST} -> ${ANSI_BOLD}${ANSI_GRE}%s${ANSI_RST}\n' "${1}" "$(2)" "$(3)"
endef
define log_tgt_start
@echo -e "$(call timestamp) [$(1)] ${ANSI_BOLD}${ANSI_GRE}$(2)${ANSI_RST} start"
endef
define log_tgt_done
@echo -e "$(call timestamp) [$(1)] ${ANSI_BOLD}${ANSI_YEL}$(2)${ANSI_RST} done"
endef

define log_info
printf '$(call timestamp) $(shell hostname) $1\n' | tee --append ${FILE_LOG_INFO}
endef

define log_failed
printf '$(call timestamp) $(shell hostname) ${ANSI_RED}$1${ANSI_RST}\n' | tee --append ${FILE_LOG_FAILED}
endef

define cleanfailedlog
	${Q}rm -f $(FILE_LOG_FAILED)
endef

define printfailedlog
	${Q}if [[ -e $(FILE_LOG_FAILED) ]]; then \
		cat $(FILE_LOG_FAILED) ; \
	fi
endef
