# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao

_VERBOSE = 1

ifeq ($(V),1)
  Q =
  MAKEFLAGS += V=1
else
  Q = @
  MAKEFLAGS += --silent
  MAKEFLAGS += --no-print-directory
endif
export Q MAKEFLAGS
