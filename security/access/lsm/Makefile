# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


sub-dir := selinux/libselinux/samples/

include ../../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	@echo $(shell ${SHELL} info.sh)
	@echo -e " \033[1;33m Done \033[m"

.PHONY: clean
clean: $(sub-dir-clean)

include ../../../template/subdir-footer.mk
