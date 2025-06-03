# SPDX-License-Identifier: GPL-3.0
${OUTPUT}:
	@echo -e "  MKDIR  \033[1m${@}\033[m"
	${Q}mkdir -p $(@)
