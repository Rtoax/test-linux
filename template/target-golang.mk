# SPDX-License-Identifier: GPL-3.0
GO ?= $(shell which go 2>/dev/null)
ifneq ($(targets-go),)
  ifeq ($(wildcard $(GO)),)
    $(error Please install golang)
  endif
endif

${targets-go}: %:
	$(call log_tgt_exe,GO,$(@).go,$(@))
	${Q}$(GO) build $(@).go
