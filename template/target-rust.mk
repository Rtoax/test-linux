# SPDX-License-Identifier: GPL-3.0
RUSTC := $(shell which rustc 2>/dev/null)
ifeq ($(RUSTC),)
  $(error "Not found rustc compiler")
endif

$(TARGETS_RUST): %:
	@echo -e "  RUSTC  \033[1;32m$(@)\033[m"
	${Q}$(RUSTC) -o $(@) $(^)
