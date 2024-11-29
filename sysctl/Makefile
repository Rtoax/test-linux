# SPDX-License-Identifier: GPL-3.0
SHELL = bash

sub-dir := sysctl.d

MAKEFLAGS :=

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e " \033[1;33m Done \033[m"

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=) MAKEFLAGS=${MAKEFLAGS} CC=$(CC) CXX=$(CXX)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) MAKEFLAGS=${MAKEFLAGS} clean
