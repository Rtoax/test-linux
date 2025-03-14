# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

include rust.mk

sub-dir :=
sub-dir += types
sub-dir += thread

TARGETS :=
TARGETS += hello
TARGETS += if-let

include ../template/subdir-header.mk

.PHONY: build
build: $(TARGETS) $(sub-dir-build)
	@echo -e "  \033[1;34mDone\033[m"

hello: hello.rs
if-let: if-let.rs


$(TARGETS): %:
	@echo -e "  RUSTC  \033[1;32m$(@)\033[m"
	${Q}$(RUSTC) -o $(@) $(^)

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS}

include ../template/subdir-footer.mk
