# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

sub-dir := openssl
sub-dir += pam
sub-dir += access
sub-dir += seccomp

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

test: $(sub-dir-test)
	@echo -e "  TEST"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(sub-dir)\033[m"

include ../template/subdir-footer.mk
