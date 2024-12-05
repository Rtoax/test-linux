# SPDX-License-Identifier: GPL-3.0
SHELL = bash

sub-dir := basic
sub-dir += icmp
sub-dir += iproute2
sub-dir += prog-test-run
#sub-dir += xdp_count

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
