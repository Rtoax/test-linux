# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../tlbuild.mk

include ../rust.mk

TARGETS :=
TARGETS += data-type

.PHONY: build
build: $(TARGETS)
	@echo -e "  \033[1;34mDone\033[m"

data-type: data-type.rs

$(TARGETS): %:
	@echo -e "  RUSTC  \033[1;32m$(@)\033[m"
	${Q}$(RUSTC) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS}
