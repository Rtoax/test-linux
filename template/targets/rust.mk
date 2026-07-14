# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao

ifndef _TARGET_RUST_MK
_TARGET_RUST_MK = 1

include rust.mk

$(target-rust-y): %:
	@$(call log_tgt,${RUSTC},$(@))
	${Q}$(RUSTC) -o $(@) $(^)

$(foreach t, ${target-rust-y}, \
  $(if $(shell test -f ${t}.rs && echo yes), \
    $(if ${DEBUG}, $(info Found ${t}.rs)) \
    $(eval ${t}: ${t}.rs), \
    $(error Not found ${t}.rs) \
  ) \
)

endif
