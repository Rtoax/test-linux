# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../../tlbuild.mk


sub-dir := selinux/libselinux/samples/

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: $(sub-dir-build)
	@echo $(shell ${SHELL} info.sh)
	@echo -e " \033[1;33m Done \033[m"

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
