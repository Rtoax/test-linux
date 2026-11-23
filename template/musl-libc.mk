# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Definitions:
# - USE_MUSL_LIBC=[y|n]
# - USE_GNU_LIBC=[n|y]
#
# - musl-libc-cflags=-D__MUSL__=1
#                    -D__MUSL_VERSION_MAJOR__=x
#                    -D__MUSL_VERSION_MINOR__=y
#
ifndef _MUSL_LIBC_MK
_MUSL_LIBC_MK = 1

musl-libc-cflags :=

# Since the vast majority of Linux distributions are GNU-based, the check for
# GNU has been placed within Musl libc.
ifeq ($(shell ldd --version 2>&1 | grep -ow musl | head -1),musl)
  export USE_MUSL_LIBC := y
  export USE_GNU_LIBC := n

  musl-libc-cflags += -D__MUSL__=1
  # TODO: use correct musl libc version
  musl-libc-cflags += -D__MUSL_VERSION_MAJOR__=1
  musl-libc-cflags += -D__MUSL_VERSION_MINOR__=1
else ifeq ($(shell ldd --version 2>&1 | grep -ow GNU | head -1),GNU)
  export USE_MUSL_LIBC := n
  export USE_GNU_LIBC := y
else
  $(error Neither GNU Libc nor Musl Libc)
endif

ifdef DEBUG
  $(info USE_MUSL_LIBC = ${USE_MUSL_LIBC})
  $(info USE_GNU_LIBC = ${USE_GNU_LIBC})
  $(info musl-libc-cflags = ${musl-libc-cflags})
endif

endif
