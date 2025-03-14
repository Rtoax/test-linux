# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk


sub-dir := samples

TARGETS :=

CC = gcc

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"

include ../template/subdir-footer.mk
