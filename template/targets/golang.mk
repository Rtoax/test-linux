# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_GOLANG_MK
_TARGET_GOLANG_MK = 1

GO ?= $(shell which go 2>/dev/null)
ifneq ($(target-go-y),)
  ifeq ($(wildcard $(GO)),)
    $(error Please install golang)
  endif
endif

${target-go-y}: %:
	$(call log_tgt,GO,$(@))
	${Q}$(GO) build $(@).go

endif
