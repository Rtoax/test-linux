# SPDX-License-Identifier: GPL-3.0
SHELL = bash

include ../bpftool.mk

SCRIPTS := $(shell find -type f -name '*.sh' -perm -001)
# Output .log suffix file list
SCRIPTS_LOG = $(patsubst %.sh,%.log,$(SCRIPTS))

sub-dir := map

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: ${SCRIPTS_LOG} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

%.log: %.sh
	@echo -e "  TEST \033[1;32m$(<) log to ${@}\033[m"
	@$(shell ${SHELL} $(<) > $(@))

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  RM \033[32m$(SCRIPTS_LOG)\033[m"
	@rm -f ${SCRIPTS_LOG} batch_example.txt

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
