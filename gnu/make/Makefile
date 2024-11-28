# SPDX-License-Identifier: GPL-3.0
SHELL = bash

.PHONY: build
build:
	@echo -e "  MK  \033[1;32m$(@)\033[m"
	@make -f patsubst.mk
	@make -f shell.mk
	@make -f wordlist.mk
	@make -f wildcard.mk
	@echo -e " \033[1;33m Done \033[m"

.PHONY: clean
clean:
