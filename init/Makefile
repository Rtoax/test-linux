# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

sub-dir := acpi
sub-dir += initrd

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
