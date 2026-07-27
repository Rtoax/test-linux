# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Definitions:
# - USE_MUSL_LIBC=[y|n]
#
ifndef _MUSL_LIBC_MK
_MUSL_LIBC_MK = 1

ifeq ($(shell ldd --version 2>&1 | grep -ow musl),)
  export USE_MUSL_LIBC := n
else
  export USE_MUSL_LIBC := y
endif

ifdef DEBUG
  $(info USE_MUSL_LIBC = ${USE_MUSL_LIBC})
endif

endif
