# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao

ifndef _TARGET_RUST_MK
export _TARGET_RUST_MK = 1

include rust.mk

$(target-rust-y): %:
	$(call log_tgt,RUSTC,$(@))
	${Q}$(RUSTC) -o $(@) $(^)

endif
