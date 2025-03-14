# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

sub-dir := examples

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) vmlinux.h
	@echo -e "  \033[1;33mDone\033[m"

include ../bpftool/vmlinux.h.mk

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  RM  \033[1mvmlinux.h\033[m"
	${Q}rm -f vmlinux.h

include ../../template/subdir-footer.mk
