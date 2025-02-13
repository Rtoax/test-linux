# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../tlbuild.mk

include ../go.mk

TARGETS :=
TARGETS += hello
TARGETS += add
TARGETS += loop
TARGETS += mutex

.PHONY: build
all: ${TARGETS}

${TARGETS}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	${Q}$(GO) build $(@).go

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS}
