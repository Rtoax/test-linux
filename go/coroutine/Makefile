SHELL = bash


GO = $(shell which go 2>/dev/null)

TARGETS :=
TARGETS += add
TARGETS += mutex

ifeq ($(wildcard $(GO)),)
  TARGETS :=
  $(warning Please install golang)
endif

.PHONY: build
all: ${TARGETS}

${TARGETS}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	@$(GO) build $(@).go

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.txt
