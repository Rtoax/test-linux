# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

sub-dir := procfs
sub-dir += ext4
sub-dir += xfs
sub-dir += fat
sub-dir += debugfs tracefs

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
