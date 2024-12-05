# SPDX-License-Identifier: GPL-3.0
SHELL = bash

sub-dir := openssl
sub-dir += pam
sub-dir += access
sub-dir += seccomp

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

test:
	@echo -e "  TEST"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(sub-dir)\033[m"

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
