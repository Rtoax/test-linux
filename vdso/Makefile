# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

include vdso.mk

sub-dir := linux-vdso.so.1
sub-dir += scripts
sub-dir += test
sub-dir += nvDSO
sub-dir += vvar/scripts/

include ../template/subdir-header.mk

$(info CMDLINE_VDSO=${CMDLINE_VDSO})

.PHONY: build
build: $(sub-dir-build)
	@${SHELL} ./dump.sh
	@${SHELL} ./layout.sh

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -rf *.so *.bt.out

include ../template/subdir-footer.mk
