# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

include bpftool.mk

sub-dir := scripts

include ../../template/subdir-header.mk

.PHONY: build
build: vmlinux.h $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

include vmlinux.h.mk

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -f vmlinux.h
	@echo -e " \033[1;33m Done \033[m"

include ../../template/subdir-footer.mk
