# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
include binutils.mk

sub-dir := bfd
sub-dir += objdump
sub-dir += opcode

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
