# SPDX-License-Identifier: GPL-3.0

include ../tlbuild.mk

sub-dir := playground

$(info INFO: USER_FAILED_LOG = ${USER_FAILED_LOG})

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
