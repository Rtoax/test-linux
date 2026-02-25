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

RUSTC := $(shell which rustc 2>/dev/null)

ifeq ($(RUSTC),)
  $(warning Not found rustc, please install first)
  export HAVE_RUSTC := n
else # Found rustc

ifdef DEBUG
  $(info RUSTC = ${RUSTC})
endif

export HAVE_RUSTC := y
export RUSTC

endif # end of found RUSTC

endif # end of _RUSTC_MK
