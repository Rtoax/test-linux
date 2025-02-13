# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

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

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
all: ${TARGETS} $(sub-dir-build)

${TARGETS}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	${Q}$(GO) build $(@).go

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.txt

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
