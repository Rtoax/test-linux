# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

include bpftool.mk

sub-dir := scripts

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: vmlinux.h $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

include vmlinux.h.mk

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -f vmlinux.h
	@echo -e " \033[1;33m Done \033[m"

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=) CC=$(CC) CXX=$(CXX)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
