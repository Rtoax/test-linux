# SPDX-License-Identifier: GPL-3.0
SHELL = bash

include ../../bpftool.mk

$(info BPFTOOL = ${BPFTOOL})

SCRIPTS := $(shell find -type f -name '*.sh' -perm -001)
# Output .log suffix file list
SCRIPTS_LOG = $(patsubst %.sh,%.log,$(SCRIPTS))

.PHONY: build
build: ${SCRIPTS_LOG}
	@echo -e " \033[1;33m Done \033[m"

%.log: %.sh
	@echo -e "  TEST \033[1;32m$(<) log to ${@}\033[m"
	@$(shell ${SHELL} $(<) > $(@))

.PHONY: clean
clean:
	@echo -e "  RM \033[32m$(SCRIPTS_LOG)\033[m"
	@rm -f ${SCRIPTS_LOG}
