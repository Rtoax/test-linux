# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

include go.mk

sub-dir := coroutine
sub-dir += os

TARGETS :=
TARGETS += hello
TARGETS += io.Copy io.Copy.Pipe io.Copy.Std
TARGETS += fibonacci
TARGETS += pi
#TARGETS += ignition
TARGETS += write
TARGETS += sleep

include ../template/subdir-header.mk

.PHONY: build
all: ${TARGETS} $(sub-dir-build)

${TARGETS}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	${Q}$(GO) build $(@).go

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.txt

include ../template/subdir-footer.mk
