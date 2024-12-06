# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


RUSTC = $(shell which rustc 2>/dev/null)

TARGETS :=
TARGETS += data-type
TARGETS += hello
TARGETS += threads
TARGETS += if-let

ifeq ($(RUSTC),)
  $(warning "Not found rustc compiler")
  TARGETS :=
endif


.PHONY: build
build: $(TARGETS)

data-type: data-type.rs
hello: hello.rs
threads: threads.rs
if-let: if-let.rs

$(TARGETS): %:
	@echo -e "  RUSTC  \033[1;32m$(@)\033[m"
	@$(RUSTC) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS}
