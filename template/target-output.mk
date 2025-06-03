# SPDX-License-Identifier: GPL-3.0
MKDIR ?= mkdir

${OUTPUT}:
	@echo -e "  MKDIR  \033[1m${@}\033[m"
	${Q}${MKDIR} -p $(@)
