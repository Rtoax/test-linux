# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Input definitions:
# - V=1
#
# Output definitions:
# - Q=[@]
#
# Append definitions:
# - MAKEFLAGS+=
#
ifndef _VERBOSE_MK
_VERBOSE_MK = 1

ifeq ($(V),1)
  Q =
  MAKEFLAGS += V=1
else
  Q = @
  MAKEFLAGS += --silent
  MAKEFLAGS += --no-print-directory
endif
export Q MAKEFLAGS

endif
