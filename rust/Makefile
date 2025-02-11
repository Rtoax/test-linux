# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include rust.mk

sub-dir :=
sub-dir += thread

TARGETS :=
TARGETS += data-type
TARGETS += hello
TARGETS += if-let

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(TARGETS) $(sub-dir-build)
	@echo -e "  \033[1;34mDone\033[m"

data-type: data-type.rs
hello: hello.rs
if-let: if-let.rs

$(sub-dir-build):
	@echo -e "  SUB-DIR  \033[1;35m$(@)\033[m"
	${Q}make -C $(@:.build=)

$(TARGETS): %:
	@echo -e "  RUSTC  \033[1;32m$(@)\033[m"
	${Q}$(RUSTC) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS}

$(sub-dir-clean):
	$(Q)make -C $(@:.clean=) clean
