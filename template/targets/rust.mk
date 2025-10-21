# SPDX-License-Identifier: GPL-3.0
_TARGET_RUST = 1

RUSTC := $(shell which rustc 2>/dev/null)
ifeq ($(RUSTC),)
  $(error "Not found rustc compiler")
endif

$(target-rust-y): %:
	$(call log_tgt_exe,RUSTC,$(<),$(@))
	${Q}$(RUSTC) -o $(@) $(^)
