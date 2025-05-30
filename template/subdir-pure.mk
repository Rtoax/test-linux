# SPDX-License-Identifier: GPL-3.0

SUBDIR_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

sub-dir ?=

include ${SUBDIR_DIR}/../tlbuild.mk
include ${SUBDIR_DIR}/subdir-header.mk
.PHONY: build
build: $(TARGETS) $(sub-dir-build)
.PHONY: clean
clean: $(sub-dir-clean)
include ${SUBDIR_DIR}/subdir-footer.mk
