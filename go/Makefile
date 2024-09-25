SHELL = bash

sub-dir := coroutine

GO = $(shell which go 2>/dev/null)

TARGETS :=
TARGETS += hello
TARGETS += io.Copy io.Copy.Pipe io.Copy.Std
TARGETS += fibonacci
TARGETS += pi
#TARGETS += ignition
TARGETS += write

ifeq ($(wildcard $(GO)),)
  TARGETS :=
  $(warning Please install golang)
endif

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)


.PHONY: build
all: ${TARGETS} $(sub-dir-build)

${TARGETS}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	@$(GO) build $(@).go

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.txt

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
