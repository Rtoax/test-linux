# SPDX-License-Identifier: GPL-3.0
GO ?= $(shell which go 2>/dev/null)
ifneq ($(TARGETS_GO),)
  ifeq ($(wildcard $(GO)),)
    $(error Please install golang)
  endif
endif

${TARGETS_GO}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	${Q}$(GO) build $(@).go
