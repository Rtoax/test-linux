# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_RUST_MK
_TARGET_RUST_MK = 1

RUSTC := $(shell which rustc 2>/dev/null)
ifeq ($(RUSTC),)
  $(error "Not found rustc compiler")
endif

$(target-rust-y): %:
	$(call log_exe,RUSTC,$(<),$(@))
	${Q}$(RUSTC) -o $(@) $(^)

endif
