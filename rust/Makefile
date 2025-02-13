# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../tlbuild.mk

include rust.mk

sub-dir :=
sub-dir += types
sub-dir += thread

TARGETS :=
TARGETS += hello
TARGETS += if-let

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: $(TARGETS) $(sub-dir-build)
	@echo -e "  \033[1;34mDone\033[m"

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
