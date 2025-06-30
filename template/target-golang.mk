# SPDX-License-Identifier: GPL-3.0
GO ?= $(shell which go 2>/dev/null)
ifneq ($(TARGETS_GO),)
  ifeq ($(wildcard $(GO)),)
    $(error Please install golang)
  endif
endif

${TARGETS_GO}: %:
	$(call log_tgt_exe,GO,$(@).go,$(@))
	${Q}$(GO) build $(@).go
