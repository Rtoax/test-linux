# SPDX-License-Identifier: GPL-3.0
_TARGET_GOLANG = 1

GO ?= $(shell which go 2>/dev/null)
ifneq ($(target-go-y),)
  ifeq ($(wildcard $(GO)),)
    $(error Please install golang)
  endif
endif

${target-go-y}: %:
	$(call log_tgt_exe,GO,$(@).go,$(@))
	${Q}$(GO) build $(@).go
