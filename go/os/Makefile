# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../go.mk

TARGETS :=
TARGETS += exec

.PHONY: build
all: ${TARGETS}

${TARGETS}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	${Q}$(GO) build $(@).go

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS}
