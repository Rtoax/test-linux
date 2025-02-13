# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

include vdso.mk

sub-dir := linux-vdso.so.1
sub-dir += scripts
sub-dir += test
sub-dir += vvar/scripts/

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

$(info CMDLINE_VDSO=${CMDLINE_VDSO})

.PHONY: build
build: $(sub-dir-build)
	@${SHELL} ./dump.sh
	@${SHELL} ./layout.sh

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -rf *.so

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
