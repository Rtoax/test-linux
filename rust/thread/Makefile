# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../rust.mk

TARGETS :=
TARGETS += threads
TARGETS += spawn

.PHONY: build
build: $(TARGETS)
	@echo -e "  \033[1;34mDone\033[m"

threads: threads.rs
spawn: spawn.rs

$(TARGETS): %:
	@echo -e "  RUSTC  \033[1;32m$(@)\033[m"
	${Q}$(RUSTC) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS}
