# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao

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
