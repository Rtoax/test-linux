# SPDX-License-Identifier: GPL-3.0
SHELL = bash

sub-dir := samples

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)
	@./info.sh raw
	@./info.sh pure
	@./info.sh c
	@echo -e " \033[1;33m Done \033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e " CLEAN \033[1;33m ${sub-dir} \033[m"
	@rm -f numa_mem.h

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
