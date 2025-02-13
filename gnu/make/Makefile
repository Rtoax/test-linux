# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../tlbuild.mk

MAKE := make

TARGETS :=
TARGETS += $(shell ls *.mk)

LOGS := $(patsubst %.mk,%.log,$(TARGETS))

ARGS_firstword := build

.PHONY: build
build: ${LOGS}
	@echo -e " \033[1;33m Done \033[m"

%.log: %.mk
	@echo -e "  MK  \033[1;32m$(@)\033[m"
	$(Q)$(MAKE) -f $(<) $(ARGS_$(*)) | tee $(@)

.PHONY: clean
clean:
	@echo -e "  RM  \033[1;32m$(LOGS)\033[m"
	${Q}rm -f ${LOGS}
