# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


MAKE := make

TARGETS :=
TARGETS += awk.mk
TARGETS += firstword.mk
TARGETS += patsubst.mk
TARGETS += shell.mk
TARGETS += subst.mk
TARGETS += wildcard.mk
TARGETS += wordlist.mk

LOGS := $(patsubst %.mk,%.log,$(TARGETS))

ARGS_firstword := build

.PHONY: build
build: ${LOGS}
	@echo -e " \033[1;33m Done \033[m"

%.log: %.mk
	@echo -e "  MK  \033[1;32m$(@)\033[m"
	@$(MAKE) -f $(<) $(ARGS_$(*)) | tee $(@)

.PHONY: clean
clean:
	@echo -e "  RM  \033[1;32m$(LOGS)\033[m"
	${Q}rm -f ${LOGS}
