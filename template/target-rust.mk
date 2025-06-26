# SPDX-License-Identifier: GPL-3.0
RUSTC := $(shell which rustc 2>/dev/null)
ifeq ($(RUSTC),)
  $(error "Not found rustc compiler")
endif

$(TARGETS_RUST): %:
	$(call log_tgt_exe,RUSTC,$(<),$(@))
	${Q}$(RUSTC) -o $(@) $(^)
