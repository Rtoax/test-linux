# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Definitions:
# - USE_MUSL_LIBC=[y|n]
# - USE_GNU_LIBC=[n|y]
#
ifndef _MUSL_LIBC_MK
_MUSL_LIBC_MK = 1

# Since the vast majority of Linux distributions are GNU-based, the check for
# GNU has been placed within Musl libc.
ifeq ($(shell ldd --version 2>&1 | grep -ow musl | head -1),musl)
  export USE_MUSL_LIBC := y
  export USE_GNU_LIBC := n
else ifeq ($(shell ldd --version 2>&1 | grep -ow GNU | head -1),GNU)
  export USE_MUSL_LIBC := n
  export USE_GNU_LIBC := y
else
  $(error Neither GNU Libc nor Musl Libc)
endif

ifdef DEBUG
  $(info USE_MUSL_LIBC = ${USE_MUSL_LIBC})
  $(info USE_GNU_LIBC = ${USE_GNU_LIBC})
endif

endif
