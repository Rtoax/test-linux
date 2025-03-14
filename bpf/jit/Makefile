# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

sub-dir :=
sub-dir += samples

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	${Q}${SHELL} info.sh

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
