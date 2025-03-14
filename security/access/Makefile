# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk


sub-dir := acl
sub-dir += lsm

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
