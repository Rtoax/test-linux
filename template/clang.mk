# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_CLANG=[y|n]
# - CLANG=
# - CLANGXX=
#
# Functions:
#
ifndef _CLANG_MK
_CLANG_MK = 1

include shell.mk

CLANG := $(shell which clang 2>/dev/null)
CLANGXX := $(shell which clang++ 2>/dev/null)

ifeq ($(CLANG),)
  $(warning Not found clang, skipping all clang targets)
  export HAVE_CLANG := n
else
  ifdef DEBUG
    $(info CLANG = ${CLANG})
    $(info CLANGXX = ${CLANGXX})
  endif

  export HAVE_CLANG := y
  export CLANG CLANGXX
endif # end of found CLANG

endif # end of _CLANG_MK
