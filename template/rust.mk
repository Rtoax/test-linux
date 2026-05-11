# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_RUSTC=[y|n]
# - RUSTC=[/usr/bin/rustc]
#
ifndef _RUSTC_MK
_RUSTC_MK = 1

include shell.mk
include define.mk

$(call find_cmd_and_def,rustc)

endif # end of _RUSTC_MK
